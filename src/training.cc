#include "training.hh"

extern std::function<int()> rand_col;
extern std::function<int()> rand_rows;

Training::Training(unsigned int wWidth, unsigned wHeight, cv::Mat3b& image, unsigned int nbrIteration) :nbrIteration_(nbrIteration) {

    //Init All Node
    Node tmp = Node();
    for (unsigned int x = 0; x < wWidth / 1; ++x)
    {
        this->network_.push_back(std::vector<Node>());
        for (unsigned int y = 0; y < wHeight / 1; ++y) {
            tmp = Node(y * 1, (y + 1) * 1, x * 1, (x + 1)* 1);
            tmp.n_X = x;
            tmp.n_Y = y;

         //std::cout << "WB = " << tmp.weight[0] <<"WG = " << tmp.weight[1] <<"WR = " << tmp.weight[2] << std::endl;
            this->network_.back().push_back(tmp);
         //std::cout << "WB = " << this->network_.back().back().weight[0] <<"WG = " << this->network_.back().back().weight[1] <<"WR = " << this->network_.back().back().weight[2] << std::endl;
        }
    }

    this->trainingDone = false;
    this->image_ = image;
    this->radius_ = std::max(wWidth,wHeight) / 2;
    this->timeCst_ = this->nbrIteration_ / std::log(this->radius_);
    this->iterationCount_ = 0;

}

void Training::train() {

    if (this->trainingDone)
        return;
    if (this->iterationCount_ < this->nbrIteration_)
    {
        double neighborRadius = 0;
        double learningRate = this->StartLearningRate_;

        currentPixel = getAPixel();
        findBMU(currentPixel);
        neighborRadius = this->radius_ * std::exp((double)-this->iterationCount_ / this->timeCst_);

        adjustAllNodeInRadius(neighborRadius, learningRate);
        learningRate = this->StartLearningRate_ * std::exp(-(double)this->iterationCount_ / this->nbrIteration_);

        ++this->iterationCount_;
    }
    else
        this->trainingDone = true;
}

cv::Vec3b Training::getAPixel() {

    std::mt19937 mt_rand(std::time(0));
        return this->image_.at<cv::Vec3b>(rand_col(), rand_rows());
}

void Training::findBMU(cv::Vec3b aPixel)
{
    double minDistance = std::numeric_limits<double>::max();
    double tmpDistance = 0;

    for (auto& v : this->network_)
        for (auto& n : v) {
            tmpDistance = n.Distance(aPixel);
            if (minDistance < n.Distance(aPixel)) {
                this->BMU_ = n;
                minDistance = tmpDistance;
            }
        }
}

std::pair<unsigned int, unsigned int> Training::findBestNode(cv::Vec3b aPixel)
{
    double minDistance = std::numeric_limits<double>::max();
    std::pair<unsigned int, unsigned int> res;

    for (auto& v : this->network_)
        for (auto& n : v) {
            if (minDistance > n.Distance(aPixel) && !n.isOccupied) {
                res.first = n.n_X;
                res.second = n.n_Y;
                minDistance = n.Distance(aPixel);
            }
        }
    return res;

}
void Training::adjustAllNodeInRadius(double radius, double learningRate)
{
    double influence = 0;

    for (auto& v : this->network_)
        for (auto& n : v) {

            double distNode2BMU = std::pow((n.n_X - this->BMU_.n_X),2) + std::pow((n.n_Y - this->BMU_.n_Y),2);

            if (distNode2BMU < radius * radius) {
                influence = std::exp(-(distNode2BMU) / (2*radius * radius));
                n.AdjustWeights(this->currentPixel, learningRate, influence);
            }
        }

}

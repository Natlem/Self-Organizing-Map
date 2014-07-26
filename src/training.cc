#include "training.hh"

Training::Training(unsigned int wWidth, unsigned wHeight, cv::Mat3b& image, unsigned int nbrIteration) :nbrIteration_(nbrIteration) {

    //Init All Node
    for (unsigned int x = 0; x < wWidth / 10; ++x)
    {
        this->network_.push_back(std::vector<Node>());
        for (unsigned int y = 0; y < wHeight / 10; ++y)
            this->network_.back().push_back(Node(y * 10, (y + 1) * 10, x * 10, (x + 1)* 10));
    }
    this->image_ = image;
    this->radius_ = std::max(wWidth,wHeight) / 2;
    this->timeCst_ = this->nbrIteration_ / std::log(this->radius_);
    this->iterationCount_ = 0;
}

void Training::train() {

    double neighborRadius = 0;
    findBMU(getAPixel());
    neighborRadius = this->radius_ * std::exp((double)-this->iterationCount_ / this->timeCst_);
    ++this->iterationCount_;
}

cv::Vec3b Training::getAPixel() {

    std::mt19937 mt_rand(std::time(0));
    auto rand_col = std::bind(std::uniform_int_distribution<int>(0,this->image_.cols - 1), mt_rand);

    auto rand_rows = std::bind(std::uniform_int_distribution<int>(0,this->image_.rows - 1), mt_rand);

    return this->image_.at<cv::Vec3b>(rand_col(), rand_rows());
}

void Training::findBMU(cv::Vec3b aPixel)
{
    std::mt19937 mt_rand(std::time(0));

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

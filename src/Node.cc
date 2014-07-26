#include "Node.hh"

extern std::function<double()>  double_rand;

Node::Node()
{

}

Node::Node(int eLeft, int eRight, int eTop, int eBottom) : eLeft(eLeft), eRight(eRight), eTop(eTop), eBottom(eBottom) {

    for (auto& d : weight) {
        d = double_rand();
    }

    n_X = this->eLeft + (double)(this->eRight - this->eLeft)/2;
    n_Y = this->eTop + (double)(this->eBottom - this->eTop)/2;
}

double Node::Distance(cv::Vec3b aPixel) {
    double res = 0;

    for (unsigned i = 0; i < 3; ++i) {
        res += pow((aPixel[i] * 100 / 255) - this->weight[i], 2);
    }
    return sqrt(res);
}

void Node::AdjustWeights(const cv::Vec3b &target,
			 const double LearningRate,
			 const double Influence)
{
  for (unsigned int w = 0; w < 3; ++w)
    weight[w] += LearningRate * Influence * (target[w] * 100/255 - weight[w]);
}

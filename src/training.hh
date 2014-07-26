#ifndef TRAINING_HH
# define TRAINING_HH

#include "Node.hh"
#include <algorithm>
#include <limits>
#include <cmath>

class Training {
    public:
        Training(unsigned int wWidth, unsigned int wHeight, cv::Mat3b& image, unsigned int nbrIteration);
        void train();
    private:
        template<typename T>
        void parseNetwork(std::function<T(Node&)> f)
        {
           for (auto& v : this->network_)
              for (auto& n : v)
                  f(n);
        }
        void findBMU(cv::Vec3b aPixel);
        cv::Vec3b getAPixel();
        Node BMU_;
        std::vector<std::vector<Node>> network_;
        cv::Mat3b image_;
        double radius_;
        unsigned int nbrIteration_;
        double timeCst_;
        unsigned int iterationCount_;
};

#endif

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
        void findBMU(cv::Vec3b& aPixel);
        Node BMU_;
        std::vector<std::vector<Node>> network_;
        cv::Mat3b image_; 
        double radius_;
        unsigned int nbrIteration_;
        double timeCst_;
        unsigned int iterationCount_;
};

#endif 

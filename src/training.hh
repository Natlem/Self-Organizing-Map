#ifndef TRAINING_HH
# define TRAINING_HH

#include "Node.hh"
#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>

class Training {
    public:
        Training(unsigned int wWidth, unsigned int wHeight, std::vector<cv::Vec3b>& data, unsigned int nbrIteration);
        void train();
        std::pair<unsigned int, unsigned int> findBestNode(cv::Vec3b aPixel);
        bool trainingDone = false;
        std::vector<std::vector<Node>> network_;
    private:
        void adjustAllNodeInRadius(double radius, double learningRate);
        void findBMU(cv::Vec3b aPixel);
        cv::Vec3b getAPixel();
        Node BMU_;
        std::vector<cv::Vec3b> data;
        double radius_;
        unsigned int nbrIteration_;
        double timeCst_;
        unsigned int iterationCount_;
        const double StartLearningRate_ = 0.1;
        cv::Vec3b currentPixel;
};

#endif

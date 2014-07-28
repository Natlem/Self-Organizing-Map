#ifndef TRAINING_HH
# define TRAINING_HH

#include "Node.hh"
#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>
#include "fastonebigheader.h"
#include "tbbFindBMU.hh"
#include "tbb/parallel_for.h"
#include "tbb/partitioner.h"

class Training {
    public:
        Training(unsigned int wWidth, unsigned int wHeight, std::vector<cv::Vec3b>& data, unsigned int nbrIteration);
        void train();
        std::pair<unsigned int, unsigned int> findBestNode(cv::Vec3b aPixel);
        bool trainingDone = false;
        std::vector<std::vector<Node>> network_;
        double learningRate = 0.1;
        void bestMultiple(int num, int&res1, int& res2);
        unsigned int networkHeight;
        unsigned int networkWidth;
        unsigned int nbrThreads = 1;
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

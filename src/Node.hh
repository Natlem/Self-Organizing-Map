#ifndef NODE_HH
# define NODE_HH

#include <chrono>
#include <iostream>
#include <functional>
#include <random>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

class Node {
    public:
        Node(int eLeft, int eRight, int eTop, int eBottom);
        Node();
        double Distance(cv::Vec3b aPixel);
        void AdjustWeights(const cv::Vec3b &target,
			   const double LearningRate,
			   const double Influence);
        double n_X; // coordinate X in the Network/Lattice
        double n_Y; // coordinate Y in the Network/Lattice
        bool isOccupied = false;
        double weight[3]; //Weights for B/G/R 0 < w < 1
    private:

        // Edge of Node
        int eLeft;
        int eRight;
        int eTop;
        int eBottom;
};

#endif

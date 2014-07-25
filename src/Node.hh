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
        double Distance(cv::Vec3b aPixel);
    private:
        double weight[3]; //Weights for B/G/R 0 < w < 1
        double n_X; // coordinate X in the Network/Lattice
        double n_Y; // coordinate Y in the Network/Lattice

        // Edge of Node
        int eLeft;
        int eRight;
        int eTop;
        int eBottom;
};

#endif 

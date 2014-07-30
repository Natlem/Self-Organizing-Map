#ifndef TBBFINDBMU_HH
# define TBBFINDBMU_HH

#include "tbb/blocked_range2d.h"
#include "Node.hh"
#include <vector>

class TBBFindBMU {
    public:
        TBBFindBMU(Node& BMU, std::vector<std::vector<Node>>& network, cv::Vec3b& aPixel);
        Node* BMU;
        const std::vector<std::vector<Node>>* network;
        cv::Vec3b* aPixel;
        void operator()(const tbb::blocked_range2d<double>& r) const;
};

#endif

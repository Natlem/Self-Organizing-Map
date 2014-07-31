#ifndef TBBCLUSTER_HH
# define TBBCLUSTER_HH

#include "training.hh"

class tbbCluster {
    public:
        tbbCluster(Training& T, cv::Mat3b& imgSRC, cv::Mat3b& imgDST);
        void operator()(const tbb::blocked_range2d<double>& r) const;
        Training* T;
        cv::Mat3b* imgSRC;
        cv::Mat3b* imgDST;
};

#endif

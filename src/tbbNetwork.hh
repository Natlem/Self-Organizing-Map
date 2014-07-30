#ifndef TBBNETWORK_HH
# define TBBNETWORK_HH

#include "Node.hh"
#include "tbb/blocked_range2d.h"
#include <vector>

class tbbNetwork {
    public:
    tbbNetwork(std::vector<std::vector<Node>>& network);
    void operator()(const tbb::blocked_range2d<double>& r) const;
    std::vector<std::vector<Node>>* network;
};


#endif

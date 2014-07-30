#include "tbbNetwork.hh"

tbbNetwork::tbbNetwork(std::vector<std::vector<Node>>& network) : network(&network) {

}

void tbbNetwork::operator()(const tbb::blocked_range2d<double>& r) const {
    Node tmp = Node();
    for (unsigned int i = r.cols().begin(); i != r.cols().end(); ++i) {
        (*network).push_back(std::vector<Node>());
        for (unsigned int j = r.rows().begin(); j != r.rows().end(); ++j)
        {
            tmp = Node(j * 1, (j + 1) * 1, i * 1, (j + 1) * 1);
            tmp.n_X = i;
            tmp.n_Y = j;
            (*network).back().push_back(tmp);
        }
    }
}

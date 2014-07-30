#include "tbbFindBMU.hh"

TBBFindBMU::TBBFindBMU(Node& BMU, std::vector<std::vector<Node>>& network, cv::Vec3b& aPixel)
: BMU(&BMU),network(&network),aPixel(&aPixel)
{

}

void TBBFindBMU::operator()(const tbb::blocked_range2d<double>& r) const {
    double minDistance = std::numeric_limits<double>::max();
    for (unsigned int i = r.cols().begin(); i != r.cols().end(); ++i)
        for (unsigned int j = r.rows().begin(); j != r.rows().end(); ++j)
        {
            if (minDistance > (*network)[i][j].Distance(*this->aPixel))
            {
                *this->BMU = (*network)[i][j];
                minDistance = (*network)[i][j].Distance(*this->aPixel);
            }
        }
}

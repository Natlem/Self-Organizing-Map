#include "tbbCluster.hh"

tbbCluster::tbbCluster(Training& T, cv::Mat3b& imgSRC, cv::Mat3b& imgDST) : T(&T), imgSRC(&imgSRC), imgDST(&imgDST)
{

}

void tbbCluster::operator()(const tbb::blocked_range2d<double>& r) const
{
    std::pair<unsigned int, unsigned int> tmpdst;
    for (unsigned int i = r.cols().begin(); i != r.cols().end(); ++i)
        for (unsigned int j = r.rows().begin(); j != r.rows().end(); ++j)
        {
            tmpdst = T->findBestNode(imgSRC->at<cv::Vec3b>(i,j));
            imgDST->at<cv::Vec3b>(tmpdst.first, tmpdst.second) = imgSRC->at<cv::Vec3b>(i,j);
        }
}

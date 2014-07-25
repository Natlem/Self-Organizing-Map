#include "training.hh"

void training(unsigned int wWidth, unsigned wHeight, cv::Mat3b& image) {
    
    //Init All Node
    std::vector<std::vector<Node>> network;
    for (unsigned int x = 0; x < wWidth / 10; ++x)
    {
        network.push_back(std::vector<Node>());
        for (unsigned int y = 0; y < wHeight / 10; ++y)
            network.back().push_back(Node(y * 10, (y + 1) * 10, x * 10, (x + 1)* 10));
    }

    std::mt19937 mt_rand(std::time(0));
    auto rand_col = std::bind(std::uniform_int_distribution<int>(0,image.cols - 1), mt_rand);

    auto rand_rows = std::bind(std::uniform_int_distribution<int>(0,image.rows - 1), mt_rand);

    cv::Vec3b aPixel = image.at<cv::Vec3b>(rand_col(), rand_rows());
   
    double minDistance = std::numeric_limits<double>::max();
    Node bmu = Node();

    for (auto& v : network)
      for (auto& n : v) {
            if (minDistance < n.Distance(aPixel)) {
                bmu = n;
            }
      }
    
}


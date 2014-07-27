#include <iostream>
#include <stdlib.h>
#include <opencv2/photo/photo.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

int main(int argc, char** argv)
{
  if( argc != 5)
  {
    std::cout <<" Usage: " << argv[0]  <<" nb_color ouput_img width heigth" << std::endl;
    return -1;
  }

  srand (time(NULL));
  unsigned int size = atoi(argv[1]);
  std::vector<cv::Vec3b> colors;

  for(unsigned int i = 0; i < size; ++i)
  {
    colors.emplace_back(rand() % 256, rand() % 256, rand() % 256);
  }

  unsigned int width = atoi(argv[3]);
  unsigned int height = atoi(argv[4]);

  cv::Mat img(width, height, cv::DataType<cv::Vec3b>::type);

  for (int i = 0; i < img.rows; ++i)
    for (int j = 0; j < img.cols; ++j)
    {
      img.at<cv::Vec3b>(i, j) = colors[rand() % colors.size()];
    }


  cv::imwrite(argv[2], img);
}

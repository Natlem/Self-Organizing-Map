#include "color.hh"

std::vector<cv::Vec3b> detecColors(cv::Mat img)
{
  std::vector<cv::Vec3b> colors;

  for (int i = 0; i < img.rows; ++i)
    for (int j = 0; j < img.cols; ++j)
      if (std::find(colors.begin(), colors.end(), img.at<cv::Vec3b>(i, j)) == colors.end())
	colors.push_back(img.at<cv::Vec3b>(i, j));
  return colors;
}

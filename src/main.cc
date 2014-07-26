#include <chrono>
#include <iostream>
#include "training.hh"

int main(int argc, char* argv[])
{
  const std::chrono::time_point<std::chrono::system_clock> start
    = std::chrono::system_clock::now();

  cv::Mat3b image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  Training nN = Training(image.cols, image.rows, image,1000);
  while (!nN.trainingDone) {
      nN.train();
  }
  cv::Vec3b tmp = image.at<cv::Vec3b>(0,0);
  std::pair<unsigned int, unsigned int> tmpdst;
  cv::Mat3b res = cv::Mat3b(image.rows, image.cols, image.type());
  res.setTo(cv::Scalar(0,0,0));
  for (int i = 0; i < image.cols; ++i)
      for (int j = 0; j < image.rows; ++j)
      {
          tmp = image.at<cv::Vec3b>(i,j);
          tmpdst = nN.findBestNode(tmp);
            res.at<cv::Vec3b>(tmpdst.first, tmpdst.second) = tmp;
      }
  cv::namedWindow("Display Windows", cv::WINDOW_AUTOSIZE);
  cv::imshow("Display Windows",res);
  cv::waitKey(0);
  const std::chrono::time_point<std::chrono::system_clock> end
    = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "Execution time : " << elapsed_seconds.count()
	    << " sec." << std::endl;

}

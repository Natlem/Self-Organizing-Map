#ifndef COLOR_HH_
# define COLOR_HH_

# include <vector>
# include <opencv2/photo/photo.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/core/core.hpp>

std::vector<cv::Vec3b> detecColors(cv::Mat img);

#endif // !COLOR_HH_

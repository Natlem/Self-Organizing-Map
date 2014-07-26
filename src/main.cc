#include <chrono>
#include <iostream>
#include "training.hh"
#include "color.hh"

std::mt19937::result_type seed  = std::time(0);
std::function<int()> double_rand = std::bind(std::uniform_int_distribution<int>(0,100), std::mt19937(seed));

std::function<int()> rand_col;

std::function<int()> rand_rows;

std::function<int()> rand_data;


int main(int argc, char* argv[])
{
    const std::chrono::time_point<std::chrono::system_clock> start
        = std::chrono::system_clock::now();


    cv::Mat3b image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

    std::vector<cv::Vec3b> data = detecColors(image);
    rand_col = std::bind(std::uniform_int_distribution<int>(0,image.cols - 1), std::mt19937(seed));

    rand_rows = std::bind(std::uniform_int_distribution<int>(0,image.rows - 1), std::mt19937(seed));

    rand_data = std::bind(std::uniform_int_distribution<int>(0,data.size() - 1), std::mt19937(seed));

    Training nN = Training(image.cols, image.rows, data,1000);

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
    cv::imwrite("result.png", res);
    cv::namedWindow("Display Windows", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Windows",res);

    cv::waitKey(0);

    const std::chrono::time_point<std::chrono::system_clock> end
        = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Execution time : " << elapsed_seconds.count()
        << " sec." << std::endl;

}

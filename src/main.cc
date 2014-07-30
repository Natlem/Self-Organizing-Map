#include <chrono>
#include <iostream>
#include "training.hh"
#include "color.hh"
#include "tbb/task_scheduler_init.h"
#include "tbbCluster.hh"

std::mt19937::result_type seed  = std::time(0);
std::function<int()> double_rand = std::bind(std::uniform_int_distribution<int>(0,100), std::mt19937(seed));

std::function<int()> rand_col;

std::function<int()> rand_rows;

std::function<int()> rand_data;

void bestMultiple(int numberOfBlock, int& res1, int& res2);

void clustImg(Training& T, cv::Mat3b& src, cv::Mat3b& dst, int nbrThreads);

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Usage : ./Prpa_Project image_name numberOfThreads" << std::endl;
        return 1;
    }
    tbb::task_scheduler_init(atoi(argv[2]));
    const std::chrono::time_point<std::chrono::system_clock> start
        = std::chrono::system_clock::now();


    cv::Mat3b image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

    std::vector<cv::Vec3b> data = detecColors(image);
    rand_col = std::bind(std::uniform_int_distribution<int>(0,image.cols - 1), std::mt19937(seed));

    rand_rows = std::bind(std::uniform_int_distribution<int>(0,image.rows - 1), std::mt19937(seed));

    rand_data = std::bind(std::uniform_int_distribution<int>(0,data.size() - 1), std::mt19937(seed));

    unsigned int nb_iteration = 5000;
    Training nN = Training(image.cols, image.rows, data, nb_iteration);
    nN.nbrThreads = atoi(argv[2]);
    while (!nN.trainingDone) {
        nN.train();
    }

    cv::Mat3b res = cv::Mat3b(image.rows, image.cols, image.type());
    clustImg(nN, image, res, atoi(argv[2]));
        const std::chrono::time_point<std::chrono::system_clock> end
        = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Execution time : " << elapsed_seconds.count()
        << " sec." << std::endl;

    cv::imwrite("result.png", res);
    cv::namedWindow("Display Windows", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Windows",res);

    cv::waitKey(0);
}

void clustImg(Training& T, cv::Mat3b& src, cv::Mat3b& dst, int nbrThreads) {
    unsigned int nbRBlockEachRow = static_cast<unsigned int>(floor(sqrt(nbrThreads)));
    unsigned int nbOfNodeR = 0;
    unsigned int nbOfNodeC = 0;
    unsigned int networkWidth = src.cols;
    unsigned int networkHeight = src.rows;

    if (nbrThreads % nbRBlockEachRow == 0)
    {
        nbOfNodeR = networkHeight / nbRBlockEachRow;
        nbOfNodeC = networkWidth / nbRBlockEachRow;
    }
    else
    {
        int cDiv = 0;
        int rDiv = 0;

        bestMultiple(nbrThreads, cDiv, rDiv);

        nbOfNodeC = networkHeight / rDiv;
        nbOfNodeR = networkWidth / cDiv;
    }

    tbb::affinity_partitioner ap;
    tbb::parallel_for(tbb::blocked_range2d<double>(0, networkWidth, nbOfNodeC, 0, networkHeight, nbOfNodeR), tbbCluster(T, src, dst), ap);

}

void bestMultiple(int numberOfBlock, int& res1, int& res2)
{
    int diff = numberOfBlock;
    int temp1 = 0;
    int temp2 = 0;

    for (int i = 1; i < numberOfBlock; ++i)
    {
        if (numberOfBlock % i == 0)
        {
            temp1 = i;
            temp2 = numberOfBlock / i;
            if (abs(temp1 - temp2) < diff)
            {
                if (temp1 >= temp2)
                {
                    res1 = temp1;
                    res2 = temp2;
                }
                else
                {
                    res1 = temp2;
                    res2 = temp1;
                }
                diff = abs(res1 - res2);
            }
        }
    }
}

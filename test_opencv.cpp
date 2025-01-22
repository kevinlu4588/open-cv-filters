#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat img = cv::Mat::zeros(100, 100, CV_8UC3);
    if (img.empty()) {
        std::cout << "OpenCV not working!" << std::endl;
        return -1;
    }
    std::cout << "OpenCV is working!" << std::endl;
    return 0;
}

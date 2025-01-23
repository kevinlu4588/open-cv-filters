#ifndef FILTER_H
#define FILTER_H

#include <opencv2/opencv.hpp>

// Function declarations
cv::Mat customGreyscale(const cv::Mat& src);
cv::Mat applySepia(const cv::Mat& src);
cv::Mat applyVignette(const cv::Mat& src, float intensity = 0.5);
cv::Mat blur5x5(const cv::Mat& src);
cv::Mat blur5x5Separable(const cv::Mat& src);

#endif // FILTER_H

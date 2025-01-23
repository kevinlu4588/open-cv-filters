#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

using namespace cv;

/**
 * Custom grayscale transformation using weighted contributions of color channels.
 */
Mat customGreyscale(const Mat& src) {
    std::vector<Mat> channels;
    split(src, channels);
    Mat b = channels[0], g = channels[1], r = channels[2];

    Mat bgrAverage = b * 0.2 + g * 0.5 + r * 0.4;
    Mat gray = 255 - bgrAverage;

    gray = max(gray, 0); // Ensure no values below 0
    gray = min(gray, 255); // Ensure no values above 255

    Mat dst;
    merge(std::vector<Mat>{gray, gray, gray}, dst);
    return dst;
}

/**
 * Applies a sepia tone filter to an image.
 */
Mat applySepia(const Mat& src) {
    Mat sepiaMatrix = (Mat_<float>(3, 3) << 
        0.272, 0.534, 0.131,
        0.349, 0.686, 0.168,
        0.393, 0.769, 0.189);

    Mat sepiaImage;
    transform(src, sepiaImage, sepiaMatrix);
    return sepiaImage;
}

/**
 * Applies a vignette effect to an image.
 */
Mat applyVignette(const Mat& src, float intensity = 0.5) {
    int rows = src.rows, cols = src.cols;

    Mat kernelX = getGaussianKernel(cols, cols * intensity);
    Mat kernelY = getGaussianKernel(rows, rows * intensity);
    Mat vignetteMask = kernelY * kernelX.t();
    normalize(vignetteMask, vignetteMask, 0, 1, NORM_MINMAX);

    Mat output = src.clone();
    for (int i = 0; i < 3; i++) {
        output.forEach<Vec3b>([&](Vec3b& pixel, const int* position) {
            pixel[i] = saturate_cast<uchar>(pixel[i] * vignetteMask.at<double>(position[0], position[1]));
        });
    }
    return output;
}

#include <opencv2/opencv.hpp>

int blur5x5_1(cv::Mat &src, cv::Mat &dst) {
    // Ensure the destination image has the same size and type as the source
    dst.create(src.size(), src.type());

    // Define the Gaussian kernel
    int kernel[5][5] = {
        {1, 2, 4, 2, 1},
        {2, 4, 8, 4, 2},
        {4, 8, 16, 8, 4},
        {2, 4, 8, 4, 2},
        {1, 2, 4, 2, 1}
    };
    int kernelSum = 256; // Sum of kernel values for normalization

    // Process each pixel, skipping the borders
    for (int y = 2; y < src.rows - 2; y++) {
        for (int x = 2; x < src.cols - 2; x++) {
            cv::Vec3f pixelSum = {0.0f, 0.0f, 0.0f};

            // Convolve with the 5x5 kernel
            for (int ky = -2; ky <= 2; ky++) {
                for (int kx = -2; kx <= 2; kx++) {
                    cv::Vec3b pixel = src.at<cv::Vec3b>(y + ky, x + kx);
                    int weight = kernel[ky + 2][kx + 2];
                    pixelSum[0] += pixel[0] * weight; // Blue channel
                    pixelSum[1] += pixel[1] * weight; // Green channel
                    pixelSum[2] += pixel[2] * weight; // Red channel
                }
            }

            // Normalize and assign the blurred value to the destination
            dst.at<cv::Vec3b>(y, x) = cv::Vec3b(
                static_cast<uchar>(pixelSum[0] / kernelSum),
                static_cast<uchar>(pixelSum[1] / kernelSum),
                static_cast<uchar>(pixelSum[2] / kernelSum)
            );
        }
    }
    return 0; // Success
}
int blur5x5_2(cv::Mat &src, cv::Mat &dst) {
    // Copy the source image to the destination image
    dst = src.clone();

    // Define the 1x5 Gaussian kernel
    int kernel[5] = {1, 2, 4, 2, 1};
    int kernelSum = 10; // Sum of 1x5 kernel values for normalization

    // Temporary buffer for intermediate results
    cv::Mat temp = src.clone();

    // Horizontal pass
    for (int y = 0; y < src.rows; y++) {
        for (int x = 2; x < src.cols - 2; x++) {
            cv::Vec3i pixelSum = {0, 0, 0};

            for (int kx = -2; kx <= 2; kx++) {
                cv::Vec3b pixel = src.at<cv::Vec3b>(y, x + kx);
                int weight = kernel[kx + 2];
                pixelSum[0] += pixel[0] * weight; // Blue channel
                pixelSum[1] += pixel[1] * weight; // Green channel
                pixelSum[2] += pixel[2] * weight; // Red channel
            }

            temp.at<cv::Vec3b>(y, x) = cv::Vec3b(
                pixelSum[0] / kernelSum,
                pixelSum[1] / kernelSum,
                pixelSum[2] / kernelSum
            );
        }
    }

    // Vertical pass
    for (int y = 2; y < src.rows - 2; y++) {
        for (int x = 0; x < src.cols; x++) {
            cv::Vec3i pixelSum = {0, 0, 0};

            for (int ky = -2; ky <= 2; ky++) {
                cv::Vec3b pixel = temp.at<cv::Vec3b>(y + ky, x);
                int weight = kernel[ky + 2];
                pixelSum[0] += pixel[0] * weight; // Blue channel
                pixelSum[1] += pixel[1] * weight; // Green channel
                pixelSum[2] += pixel[2] * weight; // Red channel
            }

            dst.at<cv::Vec3b>(y, x) = cv::Vec3b(
                pixelSum[0] / kernelSum,
                pixelSum[1] / kernelSum,
                pixelSum[2] / kernelSum
            );
        }
    }

    return 0; // Success
}
/**
 * Applies a separable 5x5 Gaussian blur filter to the image.
 */
Mat blur5x5Separable(const Mat& src) {
    Mat kernel = (Mat_<float>(1, 5) << 1, 2, 4, 2, 1) / 10.0;

    Mat intermediate, dst;
    sepFilter2D(src, intermediate, -1, kernel, kernel.t());
    return intermediate;
}

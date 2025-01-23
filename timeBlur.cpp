/*
  Bruce A. Maxwell
  Spring 2024
  CS 5330 Computer Vision

  Example of how to time an image processing task.

  Program takes a path to an image on the command line
*/

#include <cstdio> // Standard C/C++ functions like printf, scanf
#include <cstring> // C/C++ functions for working with strings
#include <cmath>
#include <sys/time.h>
#include "opencv2/opencv.hpp"

// Prototypes for the functions to test
int blur5x5_1(cv::Mat &src, cv::Mat &dst);
int blur5x5_2(cv::Mat &src, cv::Mat &dst);

// Returns a double which gives time in seconds
double getTime() {
    struct timeval cur;
    gettimeofday(&cur, NULL);
    return (cur.tv_sec + cur.tv_usec / 1000000.0);
}

int main(int argc, char *argv[]) {
    cv::Mat src; // Input image
    cv::Mat dst; // Output image
    char filename[256]; // String for the filename

    // Check if the user provided a filename
    if (argc < 2) {
        printf("Usage: %s <image filename>\n", argv[0]);
        exit(-1);
    }
    strcpy(filename, argv[1]); // Copy the second command-line argument to filename

    // Read the image
    src = cv::imread(filename); // Allocate the image data
    if (src.data == NULL) { // Check if the read was successful
        printf("Unable to read image %s\n", filename);
        exit(-1);
    }

    const int Ntimes = 10;

    //////////////////////////////
    // Timing for version 1
    double startTime = getTime();

    for (int i = 0; i < Ntimes; i++) {
        blur5x5_1(src, dst);
    }

    double endTime = getTime();
    double difference = (endTime - startTime) / Ntimes;
    printf("Time per image (1): %.4lf seconds\n", difference);

    // Save the result of version 1
    if (!dst.empty()) {
        cv::imwrite("blur5x5_1_output.jpg", dst);
        printf("Saved blurred image: blur5x5_1_output.jpg\n");
    }

    //////////////////////////////
    // Timing for version 2
    startTime = getTime();

    for (int i = 0; i < Ntimes; i++) {
        blur5x5_2(src, dst);
    }

    endTime = getTime();
    difference = (endTime - startTime) / Ntimes;
    printf("Time per image (2): %.4lf seconds\n", difference);

    // Save the result of version 2
    if (!dst.empty()) {
        cv::imwrite("blur5x5_2_output.jpg", dst);
        printf("Saved blurred image: blur5x5_2_output.jpg\n");
    }

    printf("Terminating\n");
    return 0;
}

#include <opencv2/opencv.hpp>
#include <iostream>
#include "filter.h"

using namespace cv;
using namespace std;

int main() {
    // Open the default camera
    VideoCapture cap(0, cv::CAP_AVFOUNDATION); // macOS-specific backend
    if (!cap.isOpened()) {
        cerr << "Error: Unable to open camera" << endl;
        return -1;
    }

    cout << "Press 'q' to quit." << endl;
    cout << "Press 's' to toggle Sepia." << endl;
    cout << "Press 'g' to toggle Grayscale." << endl;
    cout << "Press 'h' to toggle Custom Grayscale." << endl;
    cout << "Press 'v' to toggle Sepia + Vignette." << endl;

    // Filter toggle flags
    bool applySepiaFilter = false;
    bool applyGrayscaleFilter = false;
    bool applyCustomGrayscaleFilter = false;
    bool applySepiaVignetteFilter = false;

    while (true) {
        Mat frame, processedFrame;
        cap >> frame; // Capture a frame
        if (frame.empty()) {
            cerr << "Error: Blank frame grabbed" << endl;
            break;
        }

        // Start with the original frame
        processedFrame = frame.clone();

        // Apply filters based on toggles
        if (applySepiaFilter) {
            processedFrame = applySepia(processedFrame);
        }
        if (applyGrayscaleFilter) {
            cvtColor(processedFrame, processedFrame, COLOR_BGR2GRAY);
            cvtColor(processedFrame, processedFrame, COLOR_GRAY2BGR); // Convert back to 3 channels
        }
        if (applyCustomGrayscaleFilter) {
            processedFrame = customGreyscale(processedFrame);
        }
        if (applySepiaVignetteFilter) {
            Mat sepia = applySepia(processedFrame);
            processedFrame = applyVignette(sepia, 0.8);
        }

        // Display the processed frame
        imshow("Processed Frame", processedFrame);

        // Handle key press for toggling filters
        char key = waitKey(10);
        if (key == 'q') {
            break; // Exit on 'q'
        } else if (key == 's') {
            applySepiaFilter = !applySepiaFilter;
            cout << "Sepia filter " << (applySepiaFilter ? "enabled" : "disabled") << "." << endl;
        } else if (key == 'g') {
            applyGrayscaleFilter = !applyGrayscaleFilter;
            cout << "Grayscale filter " << (applyGrayscaleFilter ? "enabled" : "disabled") << "." << endl;
        } else if (key == 'h') {
            applyCustomGrayscaleFilter = !applyCustomGrayscaleFilter;
            cout << "Custom Grayscale filter " << (applyCustomGrayscaleFilter ? "enabled" : "disabled") << "." << endl;
        } else if (key == 'v') {
            applySepiaVignetteFilter = !applySepiaVignetteFilter;
            cout << "Sepia + Vignette filter " << (applySepiaVignetteFilter ? "enabled" : "disabled") << "." << endl;
        }
    }

    cap.release();
    destroyAllWindows();
    return 0;
}

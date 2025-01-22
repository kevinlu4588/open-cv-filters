#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Path to the image
    std::string image_path = "/Users/KevinLu/open-cv-filters-1/python_version/Screenshot 2025-01-21 at 2.25.18 PM.png"; // Replace with your image path

    // Load the image
    cv::Mat image = cv::imread(image_path);
    if (image.empty()) {
        std::cerr << "Error: Unable to load image." << std::endl;
        return -1;
    }

    // Display the image in a window
    cv::imshow("Image Viewer", image);
    std::cout << "Press 'q' to quit the program." << std::endl;

    while (true) {
        // Wait for a key press with a delay
        char key = (char)cv::waitKey(10);

        if (key == 'q') { // Quit on 'q'
            std::cout << "Quitting program." << std::endl;
            break;
        } else if (key == 's') { // Save image when 's' is pressed
            std::string save_path = "saved_image.jpg";
            if (cv::imwrite(save_path, image)) {
                std::cout << "Image saved to " << save_path << "." << std::endl;
            } else {
                std::cerr << "Error: Failed to save the image." << std::endl;
            }
        }
    }

    // Close all OpenCV windows
    cv::destroyAllWindows();
    return 0;
}

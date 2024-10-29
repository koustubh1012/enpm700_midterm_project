#include "humandetector.hpp"
#include "DepthMapApp.hpp"
#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <iostream>
#include <random>

int main() {
    // Initialize the human detector object
    HumanDetector detector_object;

    // Define focal length and rw_height for the stereo camera setup
    float focal_length = 800.0f;  // Example focal length in pixels
    
    // Create a random number generator and distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(1.4, 1.8);

    // rw_height is hieght of the person in meters
    float rw_height = dist(gen);

    // Initialize DepthCalculator with the given focal length and rw_height
    DepthCalculator depth_calculator(focal_length, rw_height);

    // Open video capture (0 for webcam, or replace with a video file path)
    cv::VideoCapture cap(0, cv::CAP_V4L2);
    if (!cap.isOpened()) {
        std::cerr << "Error: Couldn't open video capture" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        // Detect humans in the frame
        std::unordered_map<int, std::vector<int>> detectedhumans = detector_object.detectHuman(frame);

        // Iterate through detected humans and calculate/display depth
        for (const auto &pair : detectedhumans) {
            int human_id = pair.first;
            const std::vector<int>& bbox = pair.second; // Bounding box: [x, y, width, height]


            //Get total height of bounding box
            int total_height = bbox[3];

            printf("Total Height of Bounding Box: %d\n", total_height);

            // Example h value; in a real scenario, calculate it from stereo image processing
            float h = float(total_height);

            // Calculate depth
            float depth = depth_calculator.calculateDepth(h);

            // Display depth and bounding box on the frame if depth calculation was successful
            if (depth >= 0) {
                cv::Rect bounding_box(bbox[0], bbox[1], bbox[2], bbox[3]);
                depth_calculator.displayDepth(frame, depth, bounding_box);
            }

            // Output human ID and bounding box coordinates
            std::cout << "Human ID: " << human_id << " -> Bounding Box: ";
            for (int coord : bbox) {
                std::cout << coord << " ";
            }
            std::cout << "Depth: " << depth << " meters" << std::endl;
        }

        // Show the result
        cv::imshow("Human Detection with Depth", frame);

        // Break if the user presses 'q'
        if (cv::waitKey(1) == 'q') {
            break;
        }

        frame.release();
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}

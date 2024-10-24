/**
 * @file humandetector.hpp
 * @author koustubh (koustubh@umd.edu)
 * @brief Header file for Class HumanDetector
 * @version 0.1
 * @date 2024-10-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <fstream>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <vector>

/**
 * @brief HumanDetector class for detecting human
 *
 */
class HumanDetector {
public:
  /**
   * @brief Construct a new Human Detector object
   *
   * @param model_config_file
   * @param model_weight_file
   * @param class_names_files
   */
  HumanDetector(
      const std::string &model_config_file = "./config/yolov3-tiny.cfg",
      const std::string &model_weight_file = "./config/yolov3-tiny.weights",
      const std::string &class_names_files = "./config/coco.names") {
    modelConfiguration = model_config_file;
    modelWeights = model_weight_file;
    classNamesFile = class_names_files;

    // Initialize the classNames vector
    std::ifstream ifs(classNamesFile.c_str());
    std::string line;
    while (getline(ifs, line)) {
      classNames.push_back(line);
    }
    // Load the YOLO network
    net = cv::dnn::readNetFromDarknet(modelConfiguration, modelWeights);
  }

  /**
   * @brief Function to detect human and return the coordinates of bounding
   * boxes
   *
   * @param frame
   * @return std::unordered_map<int, std::vector<int>>
   */
  std::unordered_map<int, std::vector<int>> detectHuman(cv::Mat frame);

private:
  std::string modelConfiguration;
  std::string modelWeights;
  std::string classNamesFile;
  std::vector<std::string> classNames;
  cv::dnn::Net net;
};

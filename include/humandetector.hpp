/**
 * @file humandetector.hpp
 * @author koustubh (koustubh@umd.edu), Keyur Borad (kborad@umd.edu)
 * @brief Header file for Class HumanDetector
 * @version 0.1
 * @date 2024-10-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
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
      const std::string& model_config_file = "./config/yolov3-tiny.cfg",
      const std::string& model_weight_file = "./config/yolov3-tiny.weights",
      const std::string& class_names_files = "./config/coco.names") {
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
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
  }

  /**
   * @brief Function to detect human and return the coordinates of bounding
   * boxes
   *
   * @param frame
   * @return std::unordered_map<int, std::vector<int>>
   */
  std::unordered_map<int, std::vector<int>> detectHuman(cv::Mat frame);
  /**
   * @brief Post Processor to draw a bounding box and put text on the detected
   * human also done non-Max suppression to avoid dublicacy detection of same
   * human
   *
   * @param frame
   * @param outs
   * @param net
   * @param classNames
   */
  void postProcess(cv::Mat& frame, const std::vector<cv::Mat>& outs,
                   cv::dnn::Net& net,
                   const std::vector<std::string>& classNames);

 private:
  /*!< String Variable to load the model configuration file from the config
   * folder */
  std::string modelConfiguration;
  /*!< String  Variable to load the model weights  from the config folder */
  std::string modelWeights;
  /*!< String Variable named classNamesFile to load the class names from config
   * folder */
  std::string classNamesFile;
  /*!< A vector of string to convert the cvs file of class names to a vector for
   * labelling the detected object */
  std::vector<std::string> classNames;
  /*!< OPENCV class of defining DNN neuaral net for parsing the frame */
  cv::dnn::Net net;
  /*!< unordered_map of integer and Vactor that is sent as a return of the
   * detected human class*/
  std::unordered_map<int, std::vector<int>> detectedhumans;
};

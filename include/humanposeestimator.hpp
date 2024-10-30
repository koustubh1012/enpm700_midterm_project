/**
 * @file humanposeestimator.hpp
 * @author Keyur Borad (kborad@umd.edu)
 * @brief This file contains the function declaration of HumanPoseEstimator
 * class
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

#include "DepthMapApp.hpp"
#include "humandetector.hpp"

/**
 * @brief HumanPoseEstimator class contains the implementation to estimate the
 pose of human with respect to robot
 *
 */
class HumanPoseEstimator {
 public:
  HumanDetector human_detector;
  DepthCalculator depth_calculator;
  /**
   * @brief Function to estimate human pose with respect to robot's base in a
   * frame
   *
   * @param image_frame Image frame from camera
   * @return std::unordered_map<int, std::vector<float>>
   */
  std::unordered_map<int, std::vector<float>> poseEstimator(
      cv::Mat image_frame);

 private:
  cv::Mat frame;
  /**
   * @brief Function to transform the coordinates from camera frame to robot's
   * frame
   *
   * @param bbox Coordinates of bounding box
   * @param depth Depth of human with respect to camera
   * @return std::vector<float>
   */
  std::vector<float> applyPoseTransform(std::vector<int> bbox, float depth);
};

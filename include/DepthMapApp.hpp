/**
 * @file DepthMapApp.hpp
 * @brief C++ application for generating depth 
 * 
 */
#ifndef DEPTH_MAP_APP_HPP
#define DEPTH_MAP_APP_HPP
#pragma once


#include <iostream>
#include <opencv2/opencv.hpp>


/**
 * 
 * @brief Class for calculating depth from disparity
 * @authors: Swaraj M Rao, FNU Koustubh, Keyur Borad
 * @file DepthMapApp.hpp
 * @date 2024-20-10
 * @version 1.2
 * @returns None
 */
class DepthCalculator {
  public:

    // Constructor for the DepthMapApp class
    DepthCalculator(float focal_length, float baseline);
    
    // Function to calculate depth from disparity
    float calculateDepth(float disparity) const;
    
    // Function to display depth on the frame
    void displayDepth(cv::Mat &frame, float depth, const cv::Rect &bounding_box) const;

  private:

    //Focal Length of Camera 
    float focal_length;

    // Baseline of Camera
    float baseline;

};

#endif // DEPTH_MAP_APP_HPP
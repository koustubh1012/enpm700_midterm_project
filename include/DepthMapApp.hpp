/**
    * @file DepthMapApp.hpp
    * @brief Header file for the DepthMapApp class
    * @author Swaraj, Koustubh, Keyur
    * @version 1
    * @date 2021-10-30
    * @license MIT

 */
#ifndef DEPTHMAPAPP_HPP
#define DEPTHMAPAPP_HPP

#pragma once
// #include "/home/swaraj/onnxruntime-linux-x64-gpu-1.19.2/include/onnxruntime_cxx_api.h"
// #include "../onnxruntime/onnxruntime-linux-x64-gpu-1.19.2/include/onnxruntime_cxx_api.h"
#include <opencv2/opencv.hpp>
#include <vector>

// Preprocessor class for preprocessing input images
/**
    @brief Preprocessor class for preprocessing input images
    @details This class preprocesses the input image by resizing it to the required dimensions, normalizing the pixel values, and converting the image to RGB format.

 */
class Preprocessor {
public:
    void preprocess(const cv::Mat& frame, cv::Mat& input_tensor) const;
};

// Model class for MiDaS ONNX model
/**
    * @brief MidasModel class for handling the ONNX model
    * @details This class loads the ONNX model and runs inference on the input tensor.
 */
class MidasModel {
public:
    // Constructor for the MidasModel class
    MidasModel(const std::string& model_path);
    
    // Function to run inference on the input tensor
    std::vector<float> infer(const cv::Mat& input_tensor) const;

private:

    // ONNX Runtime environment, session options, session, allocator, input name, and output name
    // Ort::Env env;
    // Ort::SessionOptions session_options;
    // std::unique_ptr<Ort::Session> session;
    // Ort::AllocatorWithDefaultOptions allocator;
    const char* input_name;
    const char* output_name;
};

//class for handling the model output

/**
    * @brief Postprocessor class for handling the model output
    * @details This class postprocess the model output to get the depth map.
    */
class Postprocessor {
public:
    cv::Mat postprocess(const std::vector<float>& output, int rows, int cols) const;
};

// Main application class for running the depth map generation

/**
    * @brief DepthMapApp class for running
    * @details This class runs the depth map generation application by preprocessing the input image, running inference on the model, and postprocessing the output.
    */
class DepthMapApp {
public:
    DepthMapApp(const std::string& model_path);
    void run();

private:
    Preprocessor preprocessor;
    MidasModel model;
    Postprocessor postprocessor;
};

#endif // DEPTHMAPAPP_HPP

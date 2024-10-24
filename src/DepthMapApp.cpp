#include "DepthMapApp.hpp"
#include <iostream>

// Set the input width and height as
const int input_width = 384;
const int input_height = 384;

// Preprocessor class implementation
void Preprocessor::preprocess(const cv::Mat &frame,
                              cv::Mat &input_tensor) const {
  cv::Mat resized;
  cv::resize(frame, resized, cv::Size(input_width, input_height));
  resized.convertTo(resized, CV_32F, 1.0 / 255.0);   // Normalize
  cv::cvtColor(resized, resized, cv::COLOR_BGR2RGB);  // Convert to RGB

  input_tensor = cv::dnn::blobFromImage(resized);
}

//  MidasModel constructor
// MidasModel::MidasModel(const std::string& model_path)
//     : env(ORT_LOGGING_LEVEL_WARNING, "MidasDepthMap") {
//     // Initialize session options
//     session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

//     // Load model
//     session = std::make_unique<Ort::Session>(env, model_path.c_str(),
//     session_options);

//     Ort::AllocatorWithDefaultOptions allocator;
//     // Get input and output names
//     input_name = session->GetInputNameAllocated(0, allocator).get();
//     output_name = session->GetOutputNameAllocated(0, allocator).get();
// }

// Run inference on the input tensor
std::vector<float> MidasModel::infer(const cv::Mat &input_tensor) const {
  // Extract the output
  std::vector<float> X = {0, 1};
  return X;
}

// Postprocessor class implementation
cv::Mat Postprocessor::postprocess(const std::vector<float> &output, int rows,
                                   int cols) const {
  cv::Mat depth_map = cv::Mat(rows, cols, CV_32F, (void *)output.data());
  cv::normalize(depth_map, depth_map, 0, 1,
                cv::NORM_MINMAX);  // Normalize between 0 and 1
  return depth_map;
}

// DepthMapApp class implementation
DepthMapApp::DepthMapApp(const std::string &model_path) : model(model_path) {}

// Run the depth map generation application
void DepthMapApp::run() {
  // Open webcam for capturing frames
  cv::VideoCapture cap(0);
  if (!cap.isOpened()) {
    std::cerr << "Error: Couldn't open webcam." << std::endl;
    return;
  }

  // While loop to capture frames and run inference
  while (true) {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
      std::cerr << "Error: Blank frame grabbed." << std::endl;
      break;
    }

    // Preprocess the frame
    cv::Mat input_tensor;
    preprocessor.preprocess(frame, input_tensor);

    // Run inference
    std::vector<float> output = model.infer(input_tensor);

    // Postprocess to get the depth map
    cv::Mat depth_map = postprocessor.postprocess(output, 384, 384);

    // Resize depth map to match the input frame size
    cv::resize(depth_map, depth_map, frame.size());

    // Display depth map
    cv::imshow("Depth Map", depth_map);
    cv::imshow("Webcam", frame);

    if (cv::waitKey(1) == 27)
      break;  // Stop if 'ESC' is pressed
  }

  // Release the frames and close the windows
  cap.release();
  cv::destroyAllWindows();
}

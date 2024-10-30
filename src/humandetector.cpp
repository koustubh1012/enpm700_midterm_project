// #pragma once

#include "humandetector.hpp"

#include <opencv2/core/mat.hpp>

std::unordered_map<int, std::vector<int>> HumanDetector::detectHuman(
    cv::Mat frame) {
  // std::unordered_map<int, std::vector<int>> detectedhumans;

  cv::Mat blob;

  // Create a 4D blob from frame
  cv::dnn::blobFromImage(frame, blob, 1 / 255.0, cv::Size(416, 416),
                         cv::Scalar(0, 0, 0), true, false);

  // Set the input for the network
  net.setInput(blob);

  // Get output layer names
  std::vector<cv::String> outNames = net.getUnconnectedOutLayersNames();
  std::vector<cv::Mat> outs;

  // Forward pass to get the outputs
  net.forward(outs, outNames);

  // Post-process the output to draw bounding boxes for humans
  postProcess(frame, outs, net, classNames);

  // Release memeory for blob
  blob.release();  // Release memory of blob
  for (auto& mat : outs) {
    mat.release();  // Release memory for each Mat in outs
  }

  // detectedhumans.insert({1, {10, 20, 30, 40}});
  return detectedhumans;
}

void HumanDetector::postProcess(cv::Mat& frame,
                                const std::vector<cv::Mat>& outs,
                                cv::dnn::Net& net,
                                const std::vector<std::string>& classNames) {
  std::vector<int> classIds;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;

  float confidenceThreshold = 0.5;
  float nmsThreshold = 0.4;

  for (size_t i = 0; i < outs.size(); ++i) {
    float* data = reinterpret_cast<float*>(outs[i].data);
    for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
      cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
      cv::Point classIdPoint;
      double confidence;
      minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
      if (confidence > confidenceThreshold) {
        int centerX = static_cast<int>(data[0] * frame.cols);
        int centerY = static_cast<int>(data[1] * frame.rows);
        int width = static_cast<int>(data[2] * frame.cols);
        int height = static_cast<int>(data[3] * frame.rows);
        int left = centerX - width / 2;
        int top = centerY - height / 2;

        classIds.push_back(classIdPoint.x);
        confidences.push_back(static_cast<float>(confidence));
        boxes.push_back(cv::Rect(left, top, width, height));
      }
      scores.release();
    }
  }

  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, confidences, confidenceThreshold, nmsThreshold,
                    indices);

  detectedhumans.clear();
  for (size_t i = 0; i < indices.size(); ++i) {
    int idx = indices[i];
    cv::Rect box = boxes[idx];
    std::string label = classNames[classIds[idx]];
    label += std::to_string(i + 1);

    // Check if the detected class is a "person" (classId is 0 for "person" in
    // COCO dataset)
    if (classIds[idx] == 0) {
      rectangle(frame, box, cv::Scalar(0, 255, 0),
                3);  // Green rectangle for humans
      putText(frame, label, cv::Point(box.x, box.y - 5),
              cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
    }
    detectedhumans.insert({i, {box.x, box.y, box.width, box.height}});
  }
}

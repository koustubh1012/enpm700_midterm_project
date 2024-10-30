#include "humanposeestimator.hpp"

#include <array>
#include <vector>

std::unordered_map<int, std::vector<float>> HumanPoseEstimator::poseEstimator(
    cv::Mat image_frame) {
  frame = image_frame;
  std::unordered_map<int, std::vector<int>> detectedhumans =
      human_detector.detectHuman(frame);
  std::unordered_map<int, std::vector<float>> human_poses;
  std::vector<float> pose;

  for (const auto& pair : detectedhumans) {
    int human_id = pair.first;
    const std::vector<int>& bbox =
        pair.second;  // Bounding box: [x, y, width, height]

    // Get total height of bounding box
    int total_height = bbox[3];

    // Example h value; in a real scenario, calculate it from stereo image
    // processing
    float h = static_cast<float>(total_height);

    // Calculate depth
    float depth = depth_calculator.calculateDepth(h);

    pose = applyPoseTransform(bbox, depth);

    std::cout << "HUMAN ID: " << human_id << " POSE IN ROBOT FRAME: " << pose[0]
              << " ," << pose[1] << " ," << pose[2] << " ,\n";

    human_poses.insert(std::make_pair(human_id, pose));
  }
  return human_poses;
}

std::vector<float> HumanPoseEstimator::applyPoseTransform(std::vector<int> bbox,
                                                          float depth) {
  float x, y, z;
  x = bbox[0] + bbox[2] / 2.0;
  y = bbox[1] + bbox[3] / 2.0;
  z = depth;

  float T_camera_to_base[4][4] = {
      {1, 0, 0, 0.1}, {0, 1, 0, 0.0}, {0, 0, 1, 0.05}, {0, 0, 0, 1}};

  float object_position_camera[4] = {x / 100, y / 100, z / 100, 1};

  float object_position_base[4] = {0, 0, 0, 0};

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      object_position_base[i] +=
          T_camera_to_base[i][j] * object_position_camera[j];
    }
  }

  std::vector<float> pose = {object_position_base[0], object_position_base[1],
                             object_position_base[2]};

  return pose;
}

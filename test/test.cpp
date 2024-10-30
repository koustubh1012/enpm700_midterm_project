#include <gtest/gtest.h>
#include <vector>
#include "humanposeestimator.hpp"

TEST(HUMAN_DETECTION, NO_HUMAN_TEST) {
  HumanDetector test_object;
  cv::Mat frame = imread("test/no_human.jpg", cv::IMREAD_COLOR);
  std::unordered_map<int, std::vector<int>> detectedhumans;
  detectedhumans = test_object.detectHuman(frame);
  ASSERT_TRUE(detectedhumans.empty());
}

TEST(HUMAN_DETECTION, ONE_HUMAN_TEST) {
  HumanDetector test_object;
  cv::Mat frame = imread("test/human.jpg", cv::IMREAD_COLOR);
  std::unordered_map<int, std::vector<int>> detectedhumans;
  detectedhumans = test_object.detectHuman(frame);
  ASSERT_EQ(detectedhumans.size(), 1);
}

TEST(HUMAN_DETECTION, TWO_HUMAN_TEST) {
  HumanDetector test_object;
  cv::Mat frame = imread("test/two_human.jpg", cv::IMREAD_COLOR);
  std::unordered_map<int, std::vector<int>> detectedhumans;
  detectedhumans = test_object.detectHuman(frame);
  ASSERT_EQ(detectedhumans.size(), 2);
}

TEST(HUMAN_POSE_ESTIMATION, NO_HUMAN_TEST) {
  HumanPoseEstimator test_object;
  cv::Mat frame = imread("test/no_human.jpg", cv::IMREAD_COLOR);
  std::unordered_map<int, std::vector<float>> human_poses = test_object.poseEstimator(frame);
  ASSERT_TRUE(human_poses.empty());
}

TEST(HUMAN_POSE_ESTIMATION, ONE_HUMAN_TEST) {
  HumanPoseEstimator test_object;
  cv::Mat frame = imread("test/human.jpg", cv::IMREAD_COLOR);
  std::unordered_map<int, std::vector<float>> human_poses = test_object.poseEstimator(frame);
  ASSERT_EQ(human_poses.size(), 1);
}

TEST(HUMAN_POSE_ESTIMATION, TWO_HUMAN_TEST) {
  HumanPoseEstimator test_object;
  cv::Mat frame = imread("test/two_human.jpg", cv::IMREAD_COLOR);
  std::unordered_map<int, std::vector<float>> human_poses = test_object.poseEstimator(frame);
  ASSERT_EQ(human_poses.size(), 2);
}

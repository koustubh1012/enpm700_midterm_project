#include "humandetector.hpp"
#include <gtest/gtest.h>

TEST(HUMAN_DETECTION, NO_HUMAN_TEST){
  HumanDetector test_object;
  cv::Mat frame = imread("no_human.jpg", cv::IMREAD_COLOR);
  std::unordered_map<int, std::vector<int>> detectedhumans;
  detectedhumans = test_object.detectHuman(frame);
  ASSERT_TRUE(detectedhumans.empty());
}

TEST(HUMAN_DETECTION, ONE_HUMAN_TEST){
  HumanDetector test_object;
  cv::Mat frame = imread("human.jpg", cv::IMREAD_COLOR);
  std::unordered_map<int, std::vector<int>> detectedhumans;
  detectedhumans = test_object.detectHuman(frame);
  ASSERT_EQ(detectedhumans.size(), 1);
}

TEST(HUMAN_DETECTION, TWO_HUMAN_TEST){
  HumanDetector test_object;
  cv::Mat frame = imread("two_human.jpg", cv::IMREAD_COLOR);
  std::unordered_map<int, std::vector<int>> detectedhumans;
  detectedhumans = test_object.detectHuman(frame);
  ASSERT_EQ(detectedhumans.size(), 2);
}

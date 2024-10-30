#include "humanposeestimator.hpp"
#include <array>
#include <vector>

//Stub implementation
std::unordered_map<int, std::vector<float>> HumanPoseEstimator::poseEstimator(cv::Mat image_frame){
    frame = image_frame;
    std::unordered_map<int, std::vector<int>> detectedhumans = human_detector.detectHuman(frame);
    std::unordered_map<int, std::vector<float>> human_poses;
    std::vector<float> pose = {0.0, 0.0, 0.0};
    human_poses.insert(std::make_pair(1, pose));

    return human_poses;
}

//Stub implementation
std::vector<float> HumanPoseEstimator::applyPoseTransform(std::vector<int> bbox, float depth){

    std::vector<float> pose = {0.0, 0.0, 0.0};

    return pose;
}

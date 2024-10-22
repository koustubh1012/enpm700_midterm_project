// #pragma once

#include "humandetector.hpp"

std::unordered_map<int, std::vector<int>> HumanDetector::detectHuman(cv::Mat frame){
    std::unordered_map<int, std::vector<int>> detectedhumans;
    detectedhumans.insert({1, {10, 20, 30, 40}});
    return detectedhumans;
}
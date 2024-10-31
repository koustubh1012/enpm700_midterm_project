# Human Object detection and tracking using monocular camera
![CICD Workflow status](https://github.com/koustubh1012/enpm700_midterm_project/actions/workflows/run-unit-test-and-upload-codecov.yml/badge.svg) 
[![codecov](https://codecov.io/gh/koustubh1012/enpm700_midterm_project/graph/badge.svg?token=30E41SWVMP)](https://codecov.io/gh/koustubh1012/enpm700_midterm_project)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)



## Project Description 
This project contains code for a Human Detection and Pose Estimation (HDPE) system developed for Acme Robotics, using a monocular camera feed as the primary sensor input. It includes the deliverables for the ENPM700 Midterm Project: Software Development for Robotics.

The system is designed to detect humans in real-time, estimate their poses, and generate bounding boxes around each detected person within the camera's field of view. Additionally, it estimates the depth of each detected human relative to the robot’s frame, outputting their coordinates within the robot's reference frame. This enables the robot to avoid collisions and plan safe trajectories. By providing critical obstacle information, the perception system enhances autonomous navigation, informing the path-planning algorithm to facilitate safe and efficient movement.

This project is essential for Acme Robotics, as it offers a vital safety and navigation component, allowing robots to operate autonomously in human-occupied environments. This capability is particularly beneficial in settings like warehouses, healthcare, and service industries, where collision avoidance is paramount.


![Shell App Output](./results/output_demo.gif)

## Authors 
1) [Keyur Borad](https://github.com/keyurborad5)                     : Graduate Student, UMD
2) [FNU Koustubh](https://github.com/koustubh1012)                   : Graduate Student, UMD
3) [Swaraj Mundruppady Rao](https://github.com/SwarajMundruppadyRao) : Graduate Student, UMD



## AIP Workflow 
This project was developed using the Agile Development Process (AIP) with pair programming, following a driver-navigator model to enhance collaboration. The approach centered on Test-Driven Development (TDD), ensuring that each feature was backed by rigorous testing. A third team member acted as the code guardian, tasked with maintaining code quality, enforcing standards, and ensuring adherence to best practices. This role was crucial for upholding the project’s commitment to producing clean, reliable, and maintainable code.

The product, iteration backlog and Work Log is documented and can be found in the Google Sheet here: 
[Product_Backlog](https://docs.google.com/spreadsheets/d/1fh9gBtK0hcLDP9B47O9Ribjl_y3yS_IEFFMDYh72blE/edit?gid=0#gid=0)

The sprint planning notes can be found in the following document
[Sprint_Planning_Notes](https://docs.google.com/document/d/1RY02FLco5-oCXIZKx6IaOrWCDU1aE-_EZPOuttu1IsA/edit?usp=sharing)

The end of each phase is tagged to distinguish each sprint. Each phase of development is tagged to mark the completion of individual sprints, providing clear milestones and versioning throughout the project. UML and Activity Diagrams are available in the UML directory, offering detailed visual documentation of the system's architecture and workflows. A short video providing a brief explanation of the implementation and demo can be found below. 


## Dependencies, Models and Libraries 

OpenCV, C++17, YOLO model (ONNX)


## Installing the dependencies

To install the dependencies for this project simply run the command below on an Ubuntu system

```bash
    #Install OpenCV
    sudo apt install libopencv-dev
    # gcovr or lcov installation
    sudo apt-get install gcovr lcov
```

## Steps to recreate the output

### Building the code
Before running any of the following, ensure that you are in the main working directory (Root Folder of the directory). To build the project, execute the following commands

```bash
    # Configure the project and generate a native build system:
    cmake -S ./ -B build/
    # Compile and build the project:
    cmake --build build/ --clean-first
```
### Generating documentation 
To generate and view the Doxygen documentation of the project, run the following commands.

```bash
    # Build the documentation into the 'docs' directory using CMake:
    cmake --build build/ --target docs 
    # Open the documentation as a HTML file
    open docs/html/index.html
```
### Running the Program Executable 

To recreate the demo, use the following command:

```bash
    ./build/app/shell-app
```

### To run the tests 
Test Driven Development process was followed and the unit tests can be run by the following command:

```bash
    ./build/test/cpp-test  

```

### API Documentation 

The HumanPoseEstimator class can be used to find the pose of a human with respect to the robot's frame.
You can use the function poseEstimator() to do so, it will take a cv::Mat image frame and return a unordered
map containing human ids as keys and a float vector containing x, y, z coordinates as values
vector of length 3, containing the estimated x, y, z positions
```cpp
# Example image frame
cv::Mat image = cv::imread("path_to_image.jpg");

# initialise the object
HumanPoseEstimator pose_estimator_obj;

# Initialize the unordered map 
std::unordered_map<int, std::vector<float>> human_poses;

# get the pose of the human in the frame
human_poses = pose_estimator_obj.poseEstimator(frame);
```
## Known Issues / bugs
The human detection might fluctuate under situations like low lighting conditions 

The unit test using the ctest command does not work as it doesn't recognize that config file paths while compiling.

The code coverage is not properly generated due to the same issue of not recognizing the file path.
    
## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Disclaimer
This software is provided "as is," without any warranties or conditions, express or implied. By using this software, you acknowledge that Acme Robotics is not liable for any damages or issues arising from its use. Users are responsible for ensuring the software’s suitability and safety for their specific applications, especially in environments with humans.

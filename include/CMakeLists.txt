# Create a library called "humandetector" (in Linux, this library is created
# with the name of either libmyLib1.a or myLib1.so).

find_package(OpenCV REQUIRED)
# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

add_library (humandetector
  # list of cpp source files:
  ../src/humandetector.cpp
  )

add_library (depthmap
  # list of cpp source files:
  ../src/DepthMapApp.cpp
  )

add_library (humanposeestimator
  # list of cpp source files:
  ../src/humanposeestimator.cpp
  )

# Indicate what directories should be added to the include file search
# path when using this library.
target_include_directories(humandetector PUBLIC
  # list of directories:
  .
  )

target_include_directories(depthmap PUBLIC
  # list of directories:
  .
  )

target_link_libraries(humandetector PUBLIC
  # list of libraries
  ${OpenCV_LIBS}
  )

target_link_libraries(depthmap PUBLIC
  # list of libraries
  ${OpenCV_LIBS}
  )

  target_link_libraries(humanposeestimator PUBLIC
  # list of libraries
  humandetector
  depthmap
)

  target_compile_definitions(humandetector PUBLIC CONFIG_FILE_DIR="${PROJECT_SOURCE_DIR}/config") 

  target_include_directories(humanposeestimator PUBLIC
  # list of directories:
  .
)
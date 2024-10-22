# Create a library called "humandetector" (in Linux, this library is created
# with the name of either libmyLib1.a or myLib1.so).

find_package(OpenCV REQUIRED)
# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

add_library (humandetector
  # list of cpp source files:
  ../src/humandetector.cpp
  )

# Indicate what directories should be added to the include file search
# path when using this library.
target_include_directories(humandetector PUBLIC
  # list of directories:
  .
  )

  target_link_libraries(humandetector PUBLIC
  # list of libraries

  ${OpenCV_LIBS}
  )
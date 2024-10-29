# Any C++ source files needed to build this target (shell-app).
add_executable(shell-app
  # list of source cpp files:
  main.cpp
  )


find_package(OpenCV REQUIRED)
# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(shell-app PUBLIC
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
)

# Any dependent libraires needed to build this target.
target_link_libraries(shell-app PUBLIC
  # list of libraries
  humandetector
  depthmap
  ${OpenCV_LIBS}
  )


  

cmake_minimum_required(VERSION 3.20)
project(medical_imaging_pipeline CUDA CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(holoscan REQUIRED)
find_package(CUDA REQUIRED)

option(BUILD_BEAMFORM "Build beamforming operator" ON)
option(BUILD_ENHANCE  "Build enhancement operator"  ON)

# MATLAB GPU Coder generated CUDA libraries
if(BUILD_BEAMFORM)
  add_subdirectory(../cuda_generated/beamform beamform_lib)
endif()
if(BUILD_ENHANCE)
  add_subdirectory(../cuda_generated/enhance enhance_lib)
endif()

add_executable(medical_pipeline
  main.cpp
  operators/data_source_op.cpp
  operators/beamform_op.cpp
  operators/enhance_op.cpp
  operators/inference_op.cpp
)

target_link_libraries(medical_pipeline
  holoscan::core
  holoscan::ops::holoviz
  holoscan::ops::inference
  beamform_cuda
  enhance_cuda
)

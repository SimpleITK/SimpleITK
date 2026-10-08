cmake_minimum_required(VERSION 3.23.0...3.31.0)
project(ITKIntegration)

find_package(SimpleITK REQUIRED)

add_executable(ITKIntegration ITKIntegration.cxx)
target_link_libraries(
  ITKIntegration
  SimpleITKIO
  SimpleITKBasicFilters0
  SimpleITKBasicFilters1
  ITK::ITKCommon
  ITK::ITKCurvatureFlowModule
)

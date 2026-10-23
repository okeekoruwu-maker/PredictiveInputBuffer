cmake_minimum_required(VERSION 3.21)
project(PredictiveInputBuffer VERSION 1.1.0)
add_library(${PROJECT_NAME} SHARED src/main.cpp)
setup_geode_mod(${PROJECT_NAME})

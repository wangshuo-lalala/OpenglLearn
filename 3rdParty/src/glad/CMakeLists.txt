cmake_minimum_required(VERSION 3.14)

project(glad)

add_library(glad SHARED glad.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR})

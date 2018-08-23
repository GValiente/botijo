cmake_minimum_required(VERSION 3.4)
project(stb-image)

# Define sources:
set(SOURCES
    src/stb_image.cpp
)

# Add a library with the above sources:
add_library(${PROJECT_NAME} ${SOURCES})

# Define include directories:
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

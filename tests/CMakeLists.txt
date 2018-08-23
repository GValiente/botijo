cmake_minimum_required(VERSION 3.4)
project(botijo-tests)

# Define sources:
set(SOURCES
    src/test1.cpp
    src/test2.cpp
    src/test3.cpp
    src/test4.cpp
)

# Define test data folder:
add_definitions(-DBTJ_TEST_DATA_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/data")

# Add a executable with the above sources:
add_executable(${PROJECT_NAME} ${SOURCES})

# Define include directories:
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Link static libraries:
target_link_libraries(${PROJECT_NAME} PRIVATE botijo)

# Include catch-mini library:
add_subdirectory(3rd_party/catch-mini)
target_link_libraries(${PROJECT_NAME} PRIVATE catch-mini)

cmake_minimum_required(VERSION 3.28)
project(jack_project LANGUAGES CXX)

message(STATUS "Building the ${PROJECT_NAME} library")

# Set the information for the library to be fetched
set(LIBRARY_TAG v1.9.22)
set(LIBRARY_URL "jackaudio/jack2")
set(LIBRARY_NAME jack2)

# Fetch the library using CPM
CPMAddPackage(
    NAME ${LIBRARY_NAME}
    GITHUB_REPOSITORY ${LIBRARY_URL}
    GIT_TAG ${LIBRARY_TAG}
    GIT_SHALLOW ON
)

# Ensure the library was fetched successfully
if(NOT ${LIBRARY_NAME}_ADDED)
    message(FATAL_ERROR "The library ${LIBRARY_NAME} was not found after fetching.")
endif()

# Declare jack2 as an interface library
add_library(${LIBRARY_NAME} INTERFACE)

# Set include directories for the jack2 library
target_include_directories(
    ${LIBRARY_NAME} INTERFACE
    "$<BUILD_INTERFACE:${${LIBRARY_NAME}_SOURCE_DIR}/include>"
)

# Ensure C++17 is used for jack2
target_compile_features(${LIBRARY_NAME} INTERFACE cxx_std_17)

# Create an alias for your custom target
add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE ${LIBRARY_NAME})

# Create an alias for jack from jack2
add_library(jack ALIAS jack2)

message(STATUS "Using ${PROJECT_NAME} version: ${LIBRARY_TAG}, from: ${LIBRARY_URL}")

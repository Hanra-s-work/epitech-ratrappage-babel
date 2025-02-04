cmake_minimum_required(VERSION 3.28)
project(toml LANGUAGES CXX)

message(STATUS "Building the ${PROJECT_NAME} library")

# Set the information for the library to be fetched
set(LIBRARY_TAG v3.4.0)
set(LIBRARY_URL "marzer/tomlplusplus")
set(LIBRARY_NAME tomlplusplus)

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

# Declare tomlplusplus as an interface library
add_library(${LIBRARY_NAME} INTERFACE)

# Set include directories for the tomlplusplus library
target_include_directories(
    ${LIBRARY_NAME} INTERFACE
    "$<BUILD_INTERFACE:${${LIBRARY_NAME}_SOURCE_DIR}/include>"
)

# Ensure C++17 is used for tomlplusplus
target_compile_features(${LIBRARY_NAME} INTERFACE cxx_std_17)

# Add an alias for tomlplusplus
add_library(toml::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

# Create an alias for your custom target
add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE ${LIBRARY_NAME})

message(STATUS "Using ${PROJECT_NAME} version: ${LIBRARY_TAG}, from: ${LIBRARY_URL}")

cmake_minimum_required(VERSION 3.28)
project(asio LANGUAGES CXX)

# Inform the user about the name of the library being built
message(STATUS "Building ${PROJECT_NAME} library")

# Create an INTERFACE library since asio is header-only
add_library(${PROJECT_NAME} INTERFACE)

set(LIBRARY_TAG asio-1-32-0)
set(LIBRARY_URL "chriskohlhoff/asio")
set(LIBRARY_NAME ${PROJECT_NAME})
set(LIBRARY_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/asio-src/asio/include")

CPMAddPackage(
    NAME ${LIBRARY_NAME}
    GITHUB_REPOSITORY ${LIBRARY_URL}
    GIT_TAG ${LIBRARY_TAG}
    GIT_SHALLOW ON
)

# Display the downloaded targets for the library
get_property(TARGETS_LIST GLOBAL PROPERTY TARGETS)
message(STATUS "CPM available targets for ${LIBRARY_NAME}: ${TARGETS_LIST}")

# Ensure the fetched library exists before proceeding
if(NOT TARGET ${LIBRARY_NAME})
    message(FATAL_ERROR "The target ${LIBRARY_NAME} was not found after fetching.")
endif()

# Ensure include directories are set correctly
target_include_directories(${PROJECT_NAME} INTERFACE ${LIBRARY_INCLUDE_DIR})

# Link required libraries
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE Threads::Threads)

message(STATUS "Asio Include Dir: ${LIBRARY_INCLUDE_DIR}")

# Display the version of the fetched library
message(STATUS "Using ${PROJECT_NAME} version: ${LIBRARY_TAG}, from: ${LIBRARY_URL}")

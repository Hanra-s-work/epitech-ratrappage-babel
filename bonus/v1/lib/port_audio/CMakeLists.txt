cmake_minimum_required(VERSION 3.28)
project(port_audio LANGUAGES CXX)

# Inform the user about the name of the library being built
message(STATUS "Building ${PROJECT_NAME} library")

# Variables
set(LIBRARY_NAME portaudio)
set(LIBRARY_URL "https://github.com/PortAudio/portaudio.git")
set(LIBRARY_HASH "aa1cfb046f93b18db4d12986ddbff84cbaa952cb")

# Download PortAudio
include(FetchContent)
FetchContent_Declare(
    ${LIBRARY_NAME}
    GIT_REPOSITORY ${LIBRARY_URL}
    GIT_TAG ${LIBRARY_HASH}
)
FetchContent_MakeAvailable(${LIBRARY_NAME})

# Create an alias for 'jack' from jack2 (if not already done in the Jack library)
# This ensures PortAudio finds 'jack' even though we're using jack2.
if(NOT TARGET jack)
    add_library(jack ALIAS jack2)
endif()

# Display for the version of the fetched library
message(STATUS "Using ${PROJECT_NAME} version from commit ${LIBRARY_HASH}, from: ${LIBRARY_URL}, because (as of writing this file) the latest release is from 2021 and was not working.")

cmake_minimum_required(VERSION 3.14)
project(port_audio LANGUAGES CXX)

# Variables
set(PORTAUDIO_NAME portaudio)
set(PORTAUDIO_REPO "https://github.com/PortAudio/portaudio.git")
set(PORTAUDIO_COMMIT "aa1cfb046f93b18db4d12986ddbff84cbaa952cb")
set(PORTAUDIO_DIR "${CMAKE_BINARY_DIR}/portaudio")

# Download PortAudio
include(FetchContent)
FetchContent_Declare(
    ${PORTAUDIO_NAME}
    GIT_REPOSITORY ${PORTAUDIO_REPO}
    GIT_TAG ${PORTAUDIO_COMMIT}
)
FetchContent_MakeAvailable(${PORTAUDIO_NAME})

# Add PortAudio as a library
add_library(port_audio INTERFACE)
target_include_directories(port_audio INTERFACE ${portaudio_SOURCE_DIR}/include)
target_link_libraries(port_audio INTERFACE ${portaudio_BINARY_DIR}/libportaudio.a)

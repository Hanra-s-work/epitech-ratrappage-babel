cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PortAudioExample LANGUAGES CXX)

# Add the port_audio subdirectory to use PortAudio's own CMake configuration
add_subdirectory(lib)

# Add the main executable
add_executable(main main.cpp)

# Link the PortAudio library
# target_link_libraries(main PRIVATE lib)
target_link_libraries(main PRIVATE portaudio)

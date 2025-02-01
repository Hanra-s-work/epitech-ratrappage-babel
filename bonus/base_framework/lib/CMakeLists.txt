cmake_minimum_required(VERSION 3.28)
project(babel_libraries LANGUAGES CXX)

# Create an interface library for reusable libraries
add_library(${PROJECT_NAME} INTERFACE)

# Add the required libraries to the project in a single library to ease the importation

# Add the CPM library in the base of the library linker

# Adding cpm.cmake to the project
set(CPM_URL "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake")
set(CPM_PATH "${CMAKE_BINARY_DIR}/CPM.cmake")

file(DOWNLOAD
    ${CPM_URL}
    ${CPM_PATH}
    SHOW_PROGRESS
)

include(${CPM_PATH})

if(WIN32)
    add_definitions(-DWINDOWS)
    add_definitions(-DWINVER=0x0A00)
    add_definitions(-D_WIN32_WINNT=0x0A00)
endif()

# Display for the version of the fetched library
message(STATUS "Using CPM version: latest, from: ${CPM_URL}")

# Add the asio library
add_subdirectory(asio)

# Link Asio libraries
target_link_libraries(${PROJECT_NAME} INTERFACE asio)

# Add the opus library
add_subdirectory(opus)

# Link opus libraries
target_link_libraries(${PROJECT_NAME} INTERFACE opus)

# Add the toml library
add_subdirectory(toml)

# Link TOML libraries
# target_link_libraries(${PROJECT_NAME} INTERFACE toml)

# Add the port audio library
add_subdirectory(port_audio)

# Link port audio libraries (skipped here due to the library being downloaded in a different way)
# target_link_libraries(${PROJECT_NAME} INTERFACE port_audio)

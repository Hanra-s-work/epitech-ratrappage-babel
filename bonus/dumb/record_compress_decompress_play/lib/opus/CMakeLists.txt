cmake_minimum_required(VERSION 3.28)
project(opus_project LANGUAGES CXX)

# Setting the alias name for the library
set(LIBRARY_ALIAS opus)

message(STATUS "Building the ${LIBRARY_ALIAS} library")

# Set the information for the library to be fetched
set(LIBRARY_TAG v1.5.2)
set(LIBRARY_URL "xiph/opus")
set(LIBRARY_NAME opus_external)
set(LIBRARY_TARGET opus)
set(LIBRARY_INCLUDE_DIR ${${LIBRARY_NAME}_SOURCE_DIR}/include)

# Fetch the library
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
if(NOT TARGET ${LIBRARY_TARGET})
    message(FATAL_ERROR "The target ${LIBRARY_TARGET} was not found after fetching. Check the Opus build configuration.")
endif()

# Create an alias so we can use 'opus' as the target name
if(NOT(${LIBRARY_TARGET} STREQUAL ${LIBRARY_ALIAS}))
    add_library(${LIBRARY_ALIAS} ALIAS ${LIBRARY_TARGET})
endif()

# Ensure include directories are set correctly
target_include_directories(${LIBRARY_ALIAS} INTERFACE ${LIBRARY_INCLUDE_DIR})

# Link required libraries
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${LIBRARY_ALIAS} PRIVATE Threads::Threads)

# Set the final output name to 'opus'
if(NOT(${LIBRARY_TARGET} STREQUAL ${LIBRARY_ALIAS}))
    set_target_properties(${LIBRARY_TARGET} PROPERTIES OUTPUT_NAME "${LIBRARY_ALIAS}")
endif()

message(STATUS "Using ${LIBRARY_ALIAS} version: ${LIBRARY_TAG}, from: ${LIBRARY_URL}")

#!/bin/bash

# This script is used to check if the required tools are installed
function check_installed {
    echo "Checking: $1"
    $1 --help 1>/dev/null 2>/dev/null
    STATUS=$?
    if [ $STATUS -ne 0 ]; then
        echo "Error: $1 is not installed, please install it"
        exit $STATUS
    fi
    echo "$1 is installed"
    return $STATUS
}

echo "(c) Created by Henry Letellier"

# Check if the required tools are installed
echo "Checking for required tools"
check_installed cmake
check_installed git
check_installed g++

# Create the build folder if not present
DEST_FOLDER=build
if [ ! -d $DEST_FOLDER ]; then
    echo "Creating the $DEST_FOLDER folder"
    mkdir $DEST_FOLDER
fi

if [ $# -eq 1 ] && [ "$1" == "debug" ]; then
    PREPEND_FLAG="-DCMAKE_BUILD_TYPE=Debug --debug-output"
fi

# Run the setup
echo "Running setup"
cmake $PREPEND_FLAG -S . -B $DEST_FOLDER
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "Error: cmake failed"
    exit $STATUS
fi

# Compile the project
echo "Compiling"
cmake --build $DEST_FOLDER -j $(nproc)
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "Error: build failed"
    exit $STATUS
fi

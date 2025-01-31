function Check-Installed {
    param(
        [string]$program
    )
    
    Write-Host "Checking: $program"
    $programExists = Get-Command $program -ErrorAction SilentlyContinue
    if (-not $programExists) {
        Write-Host "Error: $program is not installed, please install it"
        exit 1
    }
    Write-Host "$program is installed"
}

Write-Host "(c) Created by Henry Letellier"

# Check for required tools
Check-Installed cmake
Check-Installed git
Check-Installed g++

# Set destination folder
$DEST_FOLDER = "build"

# Check if the destination folder exists, if not, create it
if (-not (Test-Path $DEST_FOLDER)) {
    Write-Host "Creating the $DEST_FOLDER folder"
    New-Item -ItemType Directory -Force -Path $DEST_FOLDER
}

# Run CMake setup
Write-Host "Running setup"
cmake -S . -B $DEST_FOLDER
if ($LASTEXITCODE -ne 0) {
    Write-Host "Error: cmake failed"
    exit $LASTEXITCODE
}

# Compile using CMake
Write-Host "Compiling"
cmake --build $DEST_FOLDER
if ($LASTEXITCODE -ne 0) {
    Write-Host "Error: build failed"
    exit $LASTEXITCODE
}

Write-Host "Build completed successfully!"

#!/bin/bash
# filepath: /home/brandon/Jengine/run.sh

# Exit if any command fails
set -e

# Check for write permissions in the directory
echo "=== Checking permissions ==="
if [ ! -w "$(pwd)" ] || [ -f "Makefile" -a ! -w "Makefile" ]; then
    echo "Permissions issue detected. Attempting to fix..."
    chmod u+w "$(pwd)"
    [ -f "Makefile" ] && chmod u+w "Makefile"
    [ -d "App" ] && chmod -R u+w "App"
    [ -d "Core" ] && chmod -R u+w "Core"
    [ -d "UI" ] && chmod -R u+w "UI"
    [ -d "JEngine" ] && chmod -R u+w "JEngine"
fi

# Clean any existing build files
echo "=== Cleaning previous build ==="
[ -f "Makefile" ] && make clean || true
rm -f Makefile

# Generate build files
echo "=== Generating build files ==="
chmod +x Scripts/Setup-Linux.sh
cd Scripts
bash Setup-Linux.sh
cd ..

# Build the project
echo "=== Building project ==="
make 

# Run the application
echo "=== Running application ==="
./Binaries/linux-x86_64/Debug/App/App

echo "Done!"
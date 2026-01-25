#!/bin/bash

# CMake Build Script
# Usage: ./execute.sh [command] [executable_name]

set -e  # Exit immediately if a command exits with a non-zero status

BUILD_DIR="build"
EXECUTABLE_NAME=""  # Will be auto-detected or you can set it manually

# Check for executable name argument
if [ -n "$2" ]; then
    EXECUTABLE_NAME="$2"
fi

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to find executable in build directory
find_executable() {
    if [ -n "$EXECUTABLE_NAME" ]; then
        echo "$BUILD_DIR/$EXECUTABLE_NAME"
        return
    fi
    
    # Try to find executable automatically
    local exe_files=($(find "$BUILD_DIR" -type f -executable -not -name "*.so*" -not -name "*.a" -not -path "*/CMakeFiles/*" 2>/dev/null))
    
    if [ ${#exe_files[@]} -eq 0 ]; then
        print_error "No executable found in $BUILD_DIR" >&2
        exit 1
    elif [ ${#exe_files[@]} -eq 1 ]; then
        echo "${exe_files[0]}"
    else
        print_warning "Multiple executables found. Please select one:" >&2
        for i in "${!exe_files[@]}"; do
            echo "  $((i+1)). $(basename "${exe_files[i]}")" >&2
        done
        
        local selection
        while true; do
            read -p "Enter number (1-${#exe_files[@]}): " selection >&2
            if [[ "$selection" =~ ^[0-9]+$ ]] && [ "$selection" -ge 1 ] && [ "$selection" -le "${#exe_files[@]}" ]; then
                echo "${exe_files[$((selection-1))]}"
                break
            fi
            print_error "Invalid selection. Please enter a number between 1 and ${#exe_files[@]}." >&2
        done
    fi
}

# Function to generate build files
generate_build_files() {
    print_status "Generating build files with CMake..."
    
    if [ ! -f "CMakeLists.txt" ]; then
        print_error "CMakeLists.txt not found in current directory"
        exit 1
    fi
    
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake -G "Unix Makefiles" .. || {
        print_error "Failed to generate build files"
        exit 1
    }
    cd ..
    
    if [ -f "$BUILD_DIR/compile_commands.json" ]; then
        ln -sf "$BUILD_DIR/compile_commands.json" .
        print_status "Linked compile_commands.json for clangd"
    fi
    
    print_status "Build files generated successfully"
}

# Function to build the application
build_app() {
    print_status "Building the application..."
    
    if [ ! -d "$BUILD_DIR" ]; then
        print_error "Build directory not found. Run generation first."
        exit 1
    fi
    
    cmake --build "$BUILD_DIR" || {
        print_error "Build failed"
        exit 1
    }
    
    print_status "Build completed successfully"
}

# Function to clean build directory
clean_build() {
    print_status "Cleaning build directory..."
    
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        print_status "Build directory cleaned"
    else
        print_warning "Build directory doesn't exist"
    fi
}

# Function to run the executable
run_executable() {
    print_status "Running the executable..."
    
    local exe_path=$(find_executable)
    
    if [ ! -f "$exe_path" ]; then
        print_error "Executable not found: $exe_path"
        exit 1
    fi
    
    print_status "Executing: $exe_path"
    echo "----------------------------------------"
    "$exe_path" || {
        print_error "Execution failed with exit code $?"
        exit 1
    }
    echo "----------------------------------------"
    print_status "Execution completed successfully"
}

# Function to run all steps
run_all() {
    print_status "Starting complete build process..."
    generate_build_files
    build_app
    run_executable
    print_status "All steps completed successfully!"
}

# Main script logic
case "${1:-run}" in
    "run")
        run_all
        ;;
    "generate"|"gen")
        generate_build_files
        ;;
    "build")
        build_app
        ;;
    "clean")
        clean_build
        ;;
    "execute"|"exec")
        run_executable
        ;;
    "help"|"-h"|"--help")
        echo "Usage: $0 [command] [executable_name]"
        echo ""
        echo "Commands:"
        echo "  run       Run all steps (generate, build, execute) [default]"
        echo "  generate  Generate build files only"
        echo "  build     Build the application only"
        echo "  clean     Clean build directory"
        echo "  execute   Run the executable only"
        echo "  help      Show this help message"
        echo ""
        echo "Arguments:"
        echo "  executable_name  Optional name of the executable to run (for 'run' and 'execute' commands)"
        echo ""
        echo "Environment variables:"
        echo "  EXECUTABLE_NAME  Set the executable name manually"
        ;;
    *)
        print_error "Unknown command: $1"
        echo "Use '$0 help' for usage information"
        exit 1
        ;;
esac

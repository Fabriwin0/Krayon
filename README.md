# Krayon

A modern graphics and drawing library designed for creating vibrant visual applications with ease and efficiency.

## Project Overview

Krayon is a comprehensive graphics framework that provides developers with powerful tools for rendering, drawing, and visual manipulation. Whether you're building interactive applications, creative tools, or visual effects, Krayon offers a flexible and intuitive API to bring your ideas to life.

### Key Features

- **Intuitive Drawing API**: Simple yet powerful functions for creating shapes, lines, and text
- **Advanced Graphics Support**: Full support for colors, gradients, and transformations
- **Performance Optimized**: Efficient rendering pipeline for smooth visual experiences
- **Cross-Platform**: Built to work seamlessly across different operating systems
- **Extensible Architecture**: Easy to extend and customize for specific needs

## Getting Started

### Quick Start

1. **Clone the repository**
   ```bash
   git clone https://github.com/Fabriwin0/Krayon.git
   cd Krayon
   ```

2. **Install dependencies** (see section below)

3. **Compile the project** (see Compilation Instructions)

4. **Run your first example**
   ```bash
   ./build/krayon_example
   ```

## Dependency Setup

### Prerequisites

Before building Krayon, ensure you have the following installed:

#### Core Requirements
- **C++17 or later**: Krayon requires a modern C++ compiler
- **CMake 3.16+**: For building the project
- **Git**: For version control

#### Platform-Specific Dependencies

**Linux (Ubuntu/Debian)**
```bash
sudo apt-get update
sudo apt-get install -y \
  build-essential \
  cmake \
  libx11-dev \
  libxrandr-dev \
  libxinerama-dev \
  libxcursor-dev \
  libxi-dev \
  pkg-config
```

**macOS**
```bash
# Using Homebrew
brew install cmake
```

macOS automatically includes the required graphics libraries (Cocoa, Metal).

**Windows**
- Visual Studio 2019 or later with C++ development tools
- CMake (download from https://cmake.org/download/)
- Windows SDK (included with Visual Studio)

#### Optional Dependencies

- **OpenGL**: For enhanced graphics capabilities (usually included with system)
- **Doxygen**: For building documentation
- **Git LFS**: For managing large media files

### Installing Dependencies

#### Using Package Manager (Linux/macOS)

```bash
# macOS with Homebrew
brew install cmake

# Ubuntu/Debian
sudo apt-get install build-essential cmake libx11-dev libxrandr-dev
```

#### Manual Installation

Detailed installation guides for each dependency are available in the [DEPENDENCIES.md](DEPENDENCIES.md) file.

## Compilation Instructions

### Build Steps

#### 1. Clone and Navigate
```bash
git clone https://github.com/Fabriwin0/Krayon.git
cd Krayon
```

#### 2. Create Build Directory
```bash
mkdir build
cd build
```

#### 3. Generate Build Configuration

**Linux/macOS (using Unix Makefiles)**
```bash
cmake ..
```

**macOS (using Xcode)**
```bash
cmake -G Xcode ..
```

**Windows (using Visual Studio)**
```bash
cmake -G "Visual Studio 17 2022" ..
```

#### 4. Build the Project

**Linux/macOS**
```bash
make -j$(nproc)
```

**Windows**
```bash
cmake --build . --config Release
```

#### 5. Verify Installation
```bash
# Run tests (if available)
ctest --output-on-failure

# Or run an example
./krayon_example
```

### Build Configuration Options

You can customize the build with CMake flags:

```bash
# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..

# With documentation
cmake -DBUILD_DOCS=ON ..

# With examples
cmake -DBUILD_EXAMPLES=ON ..

# With tests
cmake -DBUILD_TESTS=ON ..
```

### Troubleshooting Build Issues

**Common Issues:**

1. **CMake not found**
   - Ensure CMake is installed and added to PATH
   - Reinstall if necessary

2. **Missing dependencies**
   - Run dependency installation commands for your platform
   - Verify with `cmake --version`

3. **Compiler errors**
   - Ensure C++17 or later is available
   - Update your compiler (GCC 7+, Clang 5+, MSVC 2019+)

4. **Build failures on macOS**
   - Install Xcode Command Line Tools: `xcode-select --install`

For more help, see the [TROUBLESHOOTING.md](TROUBLESHOOTING.md) guide.

## Usage Examples

### Basic Drawing

```cpp
#include <krayon/krayon.h>

int main() {
    krayon::Window window(800, 600, "Krayon Example");
    
    while (window.isOpen()) {
        window.clear(krayon::Color::White);
        
        // Draw a circle
        window.drawCircle(400, 300, 50, krayon::Color::Blue);
        
        // Draw a rectangle
        window.drawRect(100, 100, 200, 150, krayon::Color::Red);
        
        window.display();
    }
    
    return 0;
}
```

## Project Structure

```
Krayon/
├── src/              # Source code
├── include/          # Header files
├── examples/         # Example projects
├── tests/            # Test suite
├── docs/             # Documentation
├── CMakeLists.txt    # CMake configuration
└── README.md         # This file
```

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on how to contribute to Krayon.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Support

For issues, questions, or suggestions:
- Open an issue on [GitHub Issues](https://github.com/Fabriwin0/Krayon/issues)
- Check existing documentation in the [docs/](docs/) directory
- Review [FAQ.md](FAQ.md) for common questions

## Authors

- **Fabriwin0** - Project Creator and Maintainer

## Acknowledgments

- Thanks to all contributors who have helped improve Krayon
- Special thanks to the open-source community for inspiration and support

---

**Last Updated:** January 13, 2026

For the latest information and updates, visit the [Krayon GitHub Repository](https://github.com/Fabriwin0/Krayon)

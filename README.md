# Krayon

A modern C++20 project for visualizing and understanding 4D linear algebra concepts through interactive visualization.

## Overview

Krayon is an educational visualization tool designed to help developers and mathematicians understand complex 4D linear algebra operations. Built with modern C++20 features, it combines mathematical rigor with intuitive visual representation.

## Features

- **4D Linear Algebra Visualization**: Interactive visualization of vectors, matrices, and transformations in 4D space
- **Advanced C++20 Implementation**: Leverages concepts, ranges, modules, and other modern C++ features
- **Educational Focus**: Clear demonstrations of linear algebra principles in higher dimensions
- **High-Performance Computing**: Optimized mathematical operations for efficient computation

## C++20 Core Technologies

### Language Features
- **Concepts**: Type-safe templates for linear algebra operations
- **Ranges and Views**: Efficient data processing pipelines
- **Modules**: Organized code architecture with better encapsulation
- **Coroutines**: Asynchronous computation support for heavy mathematical operations
- **Structured Bindings**: Clean syntax for tuple and array decomposition

### Design Patterns
- Generic programming with advanced template metaprogramming
- RAII principles for resource management
- Move semantics for efficient memory handling

## 4D Linear Algebra Support

### Vectors and Matrices
- 4D vector operations (dot product, cross product extensions, magnitude)
- 4D matrix transformations and compositions
- Quaternion representations for rotations
- Homogeneous coordinates for projective transformations

### Advanced Operations
- Eigenvalue and eigenvector computations
- Gram-Schmidt orthogonalization
- QR decomposition
- SVD (Singular Value Decomposition)
- Tensor operations in 4D space

### Visualization Capabilities
- Real-time 3D projections of 4D objects
- Interactive transformation controls
- Animated demonstrations of matrix operations
- Stereoscopic visualization support

## Getting Started

### Requirements
- C++20 compatible compiler (GCC 11+, Clang 14+, MSVC 2022+)
- CMake 3.20 or higher
- Graphics library (OpenGL 4.5+)

### Building
```bash
mkdir build
cd build
cmake .. -DCMAKE_CXX_STANDARD=20
make
```

### Running Examples
```bash
./krayon_demo --sample [vector|matrix|transformation|projection]
```

## Project Structure

```
Krayon/
├── include/
│   ├── algebra/          # 4D linear algebra core
│   ├── visualization/    # Graphics and rendering
│   └── math/            # Mathematical utilities
├── src/
│   ├── algebra/         # Implementation files
│   ├── visualization/   # Renderer implementation
│   └── main.cpp
├── examples/            # Sample programs and demonstrations
└── tests/              # Unit tests
```

## Example Usage

```cpp
#include <krayon/algebra/vector4d.hpp>
#include <krayon/algebra/matrix4d.hpp>
#include <krayon/visualization/renderer.hpp>

int main() {
    using namespace krayon;
    
    // Create a 4D vector
    algebra::Vector4D v{1.0, 2.0, 3.0, 4.0};
    
    // Create a transformation matrix
    algebra::Matrix4D transform = algebra::rotation_4d(angle, axis);
    
    // Apply transformation
    auto result = transform * v;
    
    // Visualize the result
    visualization::Renderer renderer;
    renderer.draw_vector(result);
    renderer.display();
    
    return 0;
}
```

## C++20 Best Practices

- **Template Concepts**: Type constraints ensure compile-time safety
- **Constexpr Evaluation**: Compile-time computation for constants
- **Aggregate Initialization**: Clean and intuitive data structure setup
- **Lambda Enhancements**: Powerful closures with template parameters

## Performance Considerations

- SIMD optimizations for vector operations
- Cache-friendly memory layouts
- Zero-cost abstractions through compile-time specialization
- Lazy evaluation using ranges library

## Contributing

Contributions are welcome! Please ensure:
1. Code follows C++20 best practices
2. All mathematical implementations are documented
3. New features include visualization demonstrations
4. Unit tests are provided for new functionality

## License

MIT License - See LICENSE file for details

## References

- [C++20 Standard Documentation](https://en.cppreference.com/)
- [4D Geometry and Visualization](https://eater.net/quaternions)
- [Modern C++ Design Patterns](https://en.wikipedia.org/wiki/Design_Patterns_(book))

## Contact

For questions or suggestions, please open an issue on the GitHub repository.

---

**Last Updated**: January 13, 2026

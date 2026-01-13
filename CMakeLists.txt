cmake_minimum_required(VERSION 3.16)
project(Krayon CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find required packages
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Magnum REQUIRED GL)
find_package(Magnum REQUIRED Sdl2Application)
find_package(ImGui REQUIRED)

# Optional: Enable compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Create the main executable
add_executable(krayon
    # Add your source files here
    # src/main.cpp
)

# Link libraries
target_link_libraries(krayon PRIVATE
    Eigen3::Eigen
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    ImGui::ImGui
)

# Include directories
target_include_directories(krayon PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Optional: Configure Magnum
set_target_properties(krayon PROPERTIES
    MACOSX_BUNDLE ON
    MACOSX_BUNDLE_EXECUTABLE_NAME krayon
)

# For ImGui integration with Magnum (if using the integration layer)
find_package(Magnum COMPONENTS ImGuiIntegration)
if(Magnum_ImGuiIntegration_FOUND)
    target_link_libraries(krayon PRIVATE Magnum::ImGuiIntegration)
endif()

# Optional: Configuration for different platforms
if(WIN32)
    set_target_properties(krayon PROPERTIES
        WIN32_EXECUTABLE ON
    )
endif()

# Optional: Enable testing
enable_testing()

# Print configuration summary
message(STATUS "=== Krayon Configuration ===")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Eigen3 found: ${Eigen3_FOUND}")
message(STATUS "Magnum found: ${Magnum_FOUND}")
message(STATUS "ImGui found: ${ImGui_FOUND}")
message(STATUS "=============================")

#pragma once

#include <concepts>
#include <cmath>
#include <array>
#include <stdexcept>

namespace Krayon::Core {

    // ==================== Scalar Concepts ====================
    
    /**
     * @concept Scalar
     * @brief Concept for scalar types that support arithmetic operations
     */
    template<typename T>
    concept Scalar = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

    /**
     * @concept FloatingPoint
     * @brief Concept for floating-point scalar types
     */
    template<typename T>
    concept FloatingPoint = std::floating_point<T>;

    /**
     * @concept Integral
     * @brief Concept for integral scalar types
     */
    template<typename T>
    concept Integral = std::integral<T> && !std::is_same_v<T, bool>;

    // ==================== Vector4 Type ====================

    /**
     * @class Vector4
     * @brief A 4-component vector type with constexpr operations support
     * @tparam T A scalar type (floating-point or integral)
     */
    template<Scalar T>
    class Vector4 {
    public:
        // Member data
        T x, y, z, w;

        // ==================== Constructors ====================

        /**
         * @brief Default constructor, initializes to zero vector
         */
        constexpr Vector4() noexcept : x(0), y(0), z(0), w(0) {}

        /**
         * @brief Constructor with all components
         */
        constexpr Vector4(T x_val, T y_val, T z_val, T w_val) noexcept
            : x(x_val), y(y_val), z(z_val), w(w_val) {}

        /**
         * @brief Constructor with xyz and w
         */
        constexpr Vector4(T x_val, T y_val, T z_val) noexcept
            : x(x_val), y(y_val), z(z_val), w(1) {}

        /**
         * @brief Constructor from single scalar (broadcast)
         */
        constexpr Vector4(T scalar) noexcept
            : x(scalar), y(scalar), z(scalar), w(scalar) {}

        /**
         * @brief Copy constructor
         */
        constexpr Vector4(const Vector4& other) noexcept = default;

        /**
         * @brief Move constructor
         */
        constexpr Vector4(Vector4&& other) noexcept = default;

        /**
         * @brief Converting constructor for compatible scalar types
         */
        template<Scalar U>
        constexpr explicit Vector4(const Vector4<U>& other) noexcept
            : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)),
              z(static_cast<T>(other.z)), w(static_cast<T>(other.w)) {}

        // ==================== Assignment Operators ====================

        constexpr Vector4& operator=(const Vector4& other) noexcept = default;
        constexpr Vector4& operator=(Vector4&& other) noexcept = default;

        // ==================== Subscript Access ====================

        constexpr T& operator[](int index) noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (index < 0 || index >= 4) {
                    throw std::out_of_range("Vector4 index out of range");
                }
            }
            return (&x)[index];
        }

        constexpr const T& operator[](int index) const noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (index < 0 || index >= 4) {
                    throw std::out_of_range("Vector4 index out of range");
                }
            }
            return (&x)[index];
        }

        // ==================== Arithmetic Operators ====================

        /**
         * @brief Element-wise addition
         */
        constexpr Vector4 operator+(const Vector4& other) const noexcept {
            return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        constexpr Vector4& operator+=(const Vector4& other) noexcept {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }

        /**
         * @brief Element-wise subtraction
         */
        constexpr Vector4 operator-(const Vector4& other) const noexcept {
            return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        constexpr Vector4& operator-=(const Vector4& other) noexcept {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }

        /**
         * @brief Unary negation
         */
        constexpr Vector4 operator-() const noexcept {
            return Vector4(-x, -y, -z, -w);
        }

        /**
         * @brief Scalar multiplication
         */
        constexpr Vector4 operator*(T scalar) const noexcept {
            return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        constexpr Vector4& operator*=(T scalar) noexcept {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }

        /**
         * @brief Element-wise multiplication
         */
        constexpr Vector4 operator*(const Vector4& other) const noexcept {
            return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
        }

        /**
         * @brief Scalar division
         */
        constexpr Vector4 operator/(T scalar) const noexcept {
            return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }

        constexpr Vector4& operator/=(T scalar) noexcept {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
            return *this;
        }

        /**
         * @brief Element-wise division
         */
        constexpr Vector4 operator/(const Vector4& other) const noexcept {
            return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
        }

        // ==================== Comparison Operators ====================

        constexpr bool operator==(const Vector4& other) const noexcept {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        constexpr bool operator!=(const Vector4& other) const noexcept {
            return !(*this == other);
        }

        // ==================== Vector Operations ====================

        /**
         * @brief Dot product (scalar product)
         */
        constexpr T dot(const Vector4& other) const noexcept {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        /**
         * @brief Cross product for 3D vectors (ignores w component)
         */
        constexpr Vector4 cross(const Vector4& other) const noexcept {
            return Vector4(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x,
                0
            );
        }

        /**
         * @brief Squared magnitude (for avoiding sqrt in comparisons)
         */
        constexpr T lengthSquared() const noexcept {
            return x * x + y * y + z * z + w * w;
        }

        /**
         * @brief Magnitude (length)
         */
        T length() const noexcept requires FloatingPoint<T> {
            return std::sqrt(lengthSquared());
        }

        /**
         * @brief Normalized vector (unit vector)
         */
        Vector4 normalize() const noexcept requires FloatingPoint<T> {
            T len = length();
            if (len > 0) {
                return *this / len;
            }
            return *this;
        }

        /**
         * @brief Constexpr absolute value per component
         */
        constexpr Vector4 abs() const noexcept {
            auto abs_scalar = [](T val) constexpr -> T {
                return val < 0 ? -val : val;
            };
            return Vector4(abs_scalar(x), abs_scalar(y), abs_scalar(z), abs_scalar(w));
        }

        /**
         * @brief Component-wise minimum
         */
        constexpr Vector4 min(const Vector4& other) const noexcept {
            auto min_scalar = [](T a, T b) constexpr -> T {
                return a < b ? a : b;
            };
            return Vector4(
                min_scalar(x, other.x),
                min_scalar(y, other.y),
                min_scalar(z, other.z),
                min_scalar(w, other.w)
            );
        }

        /**
         * @brief Component-wise maximum
         */
        constexpr Vector4 max(const Vector4& other) const noexcept {
            auto max_scalar = [](T a, T b) constexpr -> T {
                return a > b ? a : b;
            };
            return Vector4(
                max_scalar(x, other.x),
                max_scalar(y, other.y),
                max_scalar(z, other.z),
                max_scalar(w, other.w)
            );
        }

        /**
         * @brief Clamp each component
         */
        constexpr Vector4 clamp(const Vector4& minVec, const Vector4& maxVec) const noexcept {
            return min(maxVec).max(minVec);
        }

        /**
         * @brief Linear interpolation (lerp)
         */
        constexpr Vector4 lerp(const Vector4& other, T t) const noexcept {
            return *this * (1 - t) + other * t;
        }
    };

    // ==================== Free Functions for Vector4 ====================

    template<Scalar T>
    constexpr Vector4<T> operator*(T scalar, const Vector4<T>& vec) noexcept {
        return vec * scalar;
    }

    // ==================== Matrix4 Type ====================

    /**
     * @class Matrix4
     * @brief A 4x4 matrix type stored in row-major order with constexpr operations
     * @tparam T A scalar type (floating-point or integral)
     */
    template<Scalar T>
    class Matrix4 {
    public:
        // Member data: 4x4 matrix in row-major order
        std::array<std::array<T, 4>, 4> data;

        // ==================== Constructors ====================

        /**
         * @brief Default constructor, initializes to identity matrix
         */
        constexpr Matrix4() noexcept : data{} {
            data[0][0] = 1;
            data[1][1] = 1;
            data[2][2] = 1;
            data[3][3] = 1;
        }

        /**
         * @brief Constructor from explicit scalar (scalar matrix)
         */
        constexpr explicit Matrix4(T scalar) noexcept : data{} {
            data[0][0] = scalar;
            data[1][1] = scalar;
            data[2][2] = scalar;
            data[3][3] = scalar;
        }

        /**
         * @brief Constructor from 2D array
         */
        constexpr Matrix4(const std::array<std::array<T, 4>, 4>& arr) noexcept
            : data(arr) {}

        /**
         * @brief Constructor from 16 scalar values (row-major)
         */
        constexpr Matrix4(
            T m00, T m01, T m02, T m03,
            T m10, T m11, T m12, T m13,
            T m20, T m21, T m22, T m23,
            T m30, T m31, T m32, T m33) noexcept
        {
            data[0] = {m00, m01, m02, m03};
            data[1] = {m10, m11, m12, m13};
            data[2] = {m20, m21, m22, m23};
            data[3] = {m30, m31, m32, m33};
        }

        /**
         * @brief Copy constructor
         */
        constexpr Matrix4(const Matrix4& other) noexcept = default;

        /**
         * @brief Move constructor
         */
        constexpr Matrix4(Matrix4&& other) noexcept = default;

        /**
         * @brief Converting constructor
         */
        template<Scalar U>
        constexpr explicit Matrix4(const Matrix4<U>& other) noexcept {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    data[i][j] = static_cast<T>(other.data[i][j]);
                }
            }
        }

        // ==================== Assignment Operators ====================

        constexpr Matrix4& operator=(const Matrix4& other) noexcept = default;
        constexpr Matrix4& operator=(Matrix4&& other) noexcept = default;

        // ==================== Element Access ====================

        constexpr T& operator()(int row, int col) noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (row < 0 || row >= 4 || col < 0 || col >= 4) {
                    throw std::out_of_range("Matrix4 index out of range");
                }
            }
            return data[row][col];
        }

        constexpr const T& operator()(int row, int col) const noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (row < 0 || row >= 4 || col < 0 || col >= 4) {
                    throw std::out_of_range("Matrix4 index out of range");
                }
            }
            return data[row][col];
        }

        constexpr std::array<T, 4>& operator[](int row) noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (row < 0 || row >= 4) {
                    throw std::out_of_range("Matrix4 row index out of range");
                }
            }
            return data[row];
        }

        constexpr const std::array<T, 4>& operator[](int row) const noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (row < 0 || row >= 4) {
                    throw std::out_of_range("Matrix4 row index out of range");
                }
            }
            return data[row];
        }

        // ==================== Arithmetic Operators ====================

        /**
         * @brief Element-wise addition
         */
        constexpr Matrix4 operator+(const Matrix4& other) const noexcept {
            Matrix4 result;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    result.data[i][j] = data[i][j] + other.data[i][j];
                }
            }
            return result;
        }

        constexpr Matrix4& operator+=(const Matrix4& other) noexcept {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    data[i][j] += other.data[i][j];
                }
            }
            return *this;
        }

        /**
         * @brief Element-wise subtraction
         */
        constexpr Matrix4 operator-(const Matrix4& other) const noexcept {
            Matrix4 result;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    result.data[i][j] = data[i][j] - other.data[i][j];
                }
            }
            return result;
        }

        constexpr Matrix4& operator-=(const Matrix4& other) noexcept {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    data[i][j] -= other.data[i][j];
                }
            }
            return *this;
        }

        /**
         * @brief Unary negation
         */
        constexpr Matrix4 operator-() const noexcept {
            Matrix4 result;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    result.data[i][j] = -data[i][j];
                }
            }
            return result;
        }

        /**
         * @brief Scalar multiplication
         */
        constexpr Matrix4 operator*(T scalar) const noexcept {
            Matrix4 result;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    result.data[i][j] = data[i][j] * scalar;
                }
            }
            return result;
        }

        constexpr Matrix4& operator*=(T scalar) noexcept {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    data[i][j] *= scalar;
                }
            }
            return *this;
        }

        /**
         * @brief Matrix multiplication
         */
        constexpr Matrix4 operator*(const Matrix4& other) const noexcept {
            Matrix4 result(static_cast<T>(0));
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        result.data[i][j] += data[i][k] * other.data[k][j];
                    }
                }
            }
            return result;
        }

        constexpr Matrix4& operator*=(const Matrix4& other) noexcept {
            *this = *this * other;
            return *this;
        }

        /**
         * @brief Matrix-Vector multiplication
         */
        constexpr Vector4<T> operator*(const Vector4<T>& vec) const noexcept {
            return Vector4<T>(
                data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3] * vec.w,
                data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3] * vec.w,
                data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3] * vec.w,
                data[3][0] * vec.x + data[3][1] * vec.y + data[3][2] * vec.z + data[3][3] * vec.w
            );
        }

        /**
         * @brief Scalar division
         */
        constexpr Matrix4 operator/(T scalar) const noexcept {
            return *this * (static_cast<T>(1) / scalar);
        }

        constexpr Matrix4& operator/=(T scalar) noexcept {
            return *this *= (static_cast<T>(1) / scalar);
        }

        // ==================== Comparison Operators ====================

        constexpr bool operator==(const Matrix4& other) const noexcept {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (data[i][j] != other.data[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        constexpr bool operator!=(const Matrix4& other) const noexcept {
            return !(*this == other);
        }

        // ==================== Matrix Operations ====================

        /**
         * @brief Transpose the matrix
         */
        constexpr Matrix4 transpose() const noexcept {
            Matrix4 result;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    result.data[i][j] = data[j][i];
                }
            }
            return result;
        }

        /**
         * @brief Extract the 3x3 upper-left submatrix
         */
        constexpr std::array<std::array<T, 3>, 3> submatrix3x3() const noexcept {
            return {{
                {data[0][0], data[0][1], data[0][2]},
                {data[1][0], data[1][1], data[1][2]},
                {data[2][0], data[2][1], data[2][2]}
            }};
        }

        /**
         * @brief Check if matrix is identity
         */
        constexpr bool isIdentity() const noexcept {
            static constexpr Matrix4 identity;
            return *this == identity;
        }

        /**
         * @brief Determinant calculation (helper for 3x3 submatrix)
         */
        constexpr T det3x3(
            T a, T b, T c,
            T d, T e, T f,
            T g, T h, T i) const noexcept
        {
            return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
        }

        /**
         * @brief Calculate determinant of 4x4 matrix
         */
        constexpr T determinant() const noexcept {
            // Using Laplace expansion along first row
            T det = 0;

            // Cofactor expansion
            det += data[0][0] * det3x3(
                data[1][1], data[1][2], data[1][3],
                data[2][1], data[2][2], data[2][3],
                data[3][1], data[3][2], data[3][3]
            );

            det -= data[0][1] * det3x3(
                data[1][0], data[1][2], data[1][3],
                data[2][0], data[2][2], data[2][3],
                data[3][0], data[3][2], data[3][3]
            );

            det += data[0][2] * det3x3(
                data[1][0], data[1][1], data[1][3],
                data[2][0], data[2][1], data[2][3],
                data[3][0], data[3][1], data[3][3]
            );

            det -= data[0][3] * det3x3(
                data[1][0], data[1][1], data[1][2],
                data[2][0], data[2][1], data[2][2],
                data[3][0], data[3][1], data[3][2]
            );

            return det;
        }

        /**
         * @brief Get row as Vector4
         */
        constexpr Vector4<T> getRow(int row) const noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (row < 0 || row >= 4) {
                    throw std::out_of_range("Matrix4 row index out of range");
                }
            }
            return Vector4<T>(data[row][0], data[row][1], data[row][2], data[row][3]);
        }

        /**
         * @brief Get column as Vector4
         */
        constexpr Vector4<T> getColumn(int col) const noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (col < 0 || col >= 4) {
                    throw std::out_of_range("Matrix4 column index out of range");
                }
            }
            return Vector4<T>(data[0][col], data[1][col], data[2][col], data[3][col]);
        }

        /**
         * @brief Set row from Vector4
         */
        constexpr void setRow(int row, const Vector4<T>& vec) noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (row < 0 || row >= 4) {
                    throw std::out_of_range("Matrix4 row index out of range");
                }
            }
            data[row][0] = vec.x;
            data[row][1] = vec.y;
            data[row][2] = vec.z;
            data[row][3] = vec.w;
        }

        /**
         * @brief Set column from Vector4
         */
        constexpr void setColumn(int col, const Vector4<T>& vec) noexcept {
            if constexpr (!std::is_constant_evaluated()) {
                if (col < 0 || col >= 4) {
                    throw std::out_of_range("Matrix4 column index out of range");
                }
            }
            data[0][col] = vec.x;
            data[1][col] = vec.y;
            data[2][col] = vec.z;
            data[3][col] = vec.w;
        }

        /**
         * @brief Component-wise absolute values
         */
        constexpr Matrix4 abs() const noexcept {
            auto abs_scalar = [](T val) constexpr -> T {
                return val < 0 ? -val : val;
            };
            Matrix4 result;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    result.data[i][j] = abs_scalar(data[i][j]);
                }
            }
            return result;
        }
    };

    // ==================== Free Functions for Matrix4 ====================

    template<Scalar T>
    constexpr Matrix4<T> operator*(T scalar, const Matrix4<T>& mat) noexcept {
        return mat * scalar;
    }

    template<Scalar T>
    constexpr Vector4<T> operator*(const Vector4<T>& vec, const Matrix4<T>& mat) noexcept {
        return Vector4<T>(
            vec.x * mat.data[0][0] + vec.y * mat.data[1][0] + vec.z * mat.data[2][0] + vec.w * mat.data[3][0],
            vec.x * mat.data[0][1] + vec.y * mat.data[1][1] + vec.z * mat.data[2][1] + vec.w * mat.data[3][1],
            vec.x * mat.data[0][2] + vec.y * mat.data[1][2] + vec.z * mat.data[2][2] + vec.w * mat.data[3][2],
            vec.x * mat.data[0][3] + vec.y * mat.data[1][3] + vec.z * mat.data[2][3] + vec.w * mat.data[3][3]
        );
    }

    // ==================== Type Aliases ====================

    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;
    using Vector4i = Vector4<int>;
    using Vector4u = Vector4<unsigned int>;

    using Matrix4f = Matrix4<float>;
    using Matrix4d = Matrix4<double>;
    using Matrix4i = Matrix4<int>;
    using Matrix4u = Matrix4<unsigned int>;

} // namespace Krayon::Core

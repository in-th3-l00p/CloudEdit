#ifndef APPLICATION_MATH_H
#define APPLICATION_MATH_H

#include <cmath>

namespace Math {
    // implement a Vector2 class with operator overloading
    template<typename T>
    struct Vector2 {
        T x, y;
        Vector2() = default;
        Vector2(T x, T y): x(x), y(y) {}
        Vector2(const Vector2<T>& other): x(other.x), y(other.y) {}

        Vector2<T> operator+(const Vector2<T>& other) const {
            return Vector2<T>(x + other.x, y + other.y);
        }

        Vector2<T> operator-(const Vector2<T>& other) const {
            return Vector2<T>(x - other.x, y - other.y);
        }

        Vector2<T> operator*(const Vector2<T>& other) const {
            return Vector2<T>(x * other.x, y * other.y);
        }

        Vector2<T> operator/(const Vector2<T>& other) const {
            return Vector2<T>(x / other.x, y / other.y);
        }

        Vector2<T> operator*(const T& scalar) const {
            return Vector2<T>(x * scalar, y * scalar);
        }

        Vector2<T> operator/(const T& scalar) const {
            return Vector2<T>(x / scalar, y / scalar);
        }

        Vector2<T>& operator+=(const Vector2<T>& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2<T>& operator-=(const Vector2<T>& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2<T>& operator*=(const Vector2<T>& other) {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        Vector2<T>& operator/=(const Vector2<T>& other) {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        Vector2<T>& operator*=(const T& scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2<T>& operator/=(const T& scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        bool operator==(const Vector2<T>& other) const {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vector2<T>& other) const {
            return x != other.x || y != other.y;
        }

        Vector2<T> operator-() const {
            return Vector2<T>(-x, -y);
        }

        T dot(const Vector2<T>& other) const {
            return x * other.x + y * other.y;
        }

        T length() const {
            return sqrt(x * x + y * y);
        }

        Vector2<T> normalized() const {
            return *this / length();
        }

        Vector2<T> abs() const {
            return Vector2<T>(std::abs(x), std::abs(y));
        }

        Vector2<T> min(const Vector2<T>& other) const {
            return Vector2<T>(std::min(x, other.x), std::min(y, other.y));
        }

        Vector2<T> max(const Vector2<T>& other) const {
            return Vector2<T>(std::max(x, other.x), std::max(y, other.y));
        }

        Vector2<T> clamp(const Vector2<T>& min, const Vector2<T>& max) const {
            return this->min(max).max(min);
        }

        Vector2<T> lerp(const Vector2<T>& other, const T& t) const {
            return *this * (1 - t) + other * t;
        }

        Vector2<T> lerp(const Vector2<T>& other, const Vector2<T>& t) const {
            return *this * (Vector2<T>(1, 1) - t) + other * t;
        }

        Vector2<T> project(const Vector2<T>& other) const {
            return other * (dot(other) / other.dot(other));
        }

        Vector2<T> reflect(const Vector2<T>& normal) const {
            return *this - normal * 2 * dot(normal);
        }

        Vector2<T> refract(const Vector2<T>& normal, const T& eta) const {
            T k = 1 - eta * eta * (1 - dot(normal) * dot(normal));
            if (k < 0) {
                return Vector2<T>(0, 0);
            } else {
                return *this * eta - normal * (eta * dot(normal) + sqrt(k));
            }
        }

        Vector2<T> rotate(const T& angle) const {
            T s = sin(angle);
            T c = cos(angle);
            return Vector2<T>(x * c - y * s, x * s + y * c);
        }

        Vector2<T> rotate(const Vector2<T>& center, const T& angle) const {
            return (*this - center).rotate(angle) + center;
        }

        Vector2<T> rotate(const Vector2<T>& axis, const Vector2<T>& center, const T& angle) const {
            return (*this - center).rotate(angle) + center;
        }

        Vector2<T> scale(const Vector2<T>& other) const {
            return Vector2<T>(x * other.x, y * other.y);
        }

        Vector2<T> scale(const Vector2<T>& center, const Vector2<T>& other) const {
            return (*this - center).scale(other) + center;
        }

        Vector2<T> scale(const Vector2<T>& axis, const Vector2<T>& center, const Vector2<T>& other) const {
            return (*this - center).scale(other) + center;
        }

        Vector2<T> translate(const Vector2<T>& other) const {
            return *this + other;
        }

        Vector2<T> translate(const Vector2<T>& axis, const Vector2<T>& other) const {
            return *this + other;
        }

        Vector2<T> translate(const Vector2<T>& axis, const Vector2<T>& center, const Vector2<T>& other) const {
            return *this + other;
        }

        Vector2<T> transform(const Vector2<T>& position, const Vector2<T>& scale, const T& angle) const {
            return (*this - position).rotate(angle).scale(scale) + position;
        }

        Vector2<T> transform(const Vector2<T>& position, const Vector2<T>& scale, const Vector2<T>& center, const T& angle) const {
            return (*this - position).rotate(angle).scale(scale) + position;
        }

        Vector2<T> transform(const Vector2<T>& position, const Vector2<T>& scale, const Vector2<T>& axis, const Vector2<T>& center, const T& angle) const {
            return (*this - position).rotate(angle).scale(scale) + position;
        }
    };
}

#endif //APPLICATION_MATH_H

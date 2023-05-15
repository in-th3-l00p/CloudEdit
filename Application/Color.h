#ifndef APPLICATION_COLOR_H
#define APPLICATION_COLOR_H

#include <SDL2/SDL.h>

namespace UI {
    struct Color {
        unsigned char r, g, b, a;

        Color() = default;
        Color(
                unsigned char r,
                unsigned char g,
                unsigned char b,
                unsigned char a = 255
        ): r(r), g(g), b(b), a(a) {}

        Color(const Color& other): r(other.r), g(other.g), b(other.b), a(other.a) {}

        Color& operator=(const Color& other) {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
            return *this;
        }

        Color operator+(const Color& other) const {
            return Color(r + other.r, g + other.g, b + other.b, a + other.a);
        }

        Color operator-(const Color& other) const {
            return Color(r - other.r, g - other.g, b - other.b, a - other.a);
        }

        Color operator*(const Color& other) const {
            return Color(r * other.r, g * other.g, b * other.b, a * other.a);
        }

        Color operator/(const Color& other) const {
            return Color(r / other.r, g / other.g, b / other.b, a / other.a);
        }

        Color operator*(const float& scalar) const {
            return Color(r * scalar, g * scalar, b * scalar, a * scalar);
        }

        Color operator/(const float& scalar) const {
            return Color(r / scalar, g / scalar, b / scalar, a / scalar);
        }

        Color& operator+=(const Color& other) {
            r += other.r;
            g += other.g;
            b += other.b;
            a += other.a;
            return *this;
        }

        Color& operator-=(const Color& other) {
            r -= other.r;
            g -= other.g;
            b -= other.b;
            a -= other.a;
            return *this;
        }

        Color& operator*=(const Color& other) {
            r *= other.r;
            g *= other.g;
            b *= other.b;
            a *= other.a;
            return *this;
        }

        Color& operator/=(const Color& other) {
            r /= other.r;
            g /= other.g;
            b /= other.b;
            a /= other.a;
            return *this;
        }

        Color& operator*=(const float& scalar) {
            r *= scalar;
            g *= scalar;
            b *= scalar;
            a *= scalar;
            return *this;
        }

        Color& operator/=(const float& scalar) {
            r /= scalar;
            g /= scalar;
            b /= scalar;
            a /= scalar;
            return *this;
        }

        bool operator==(const Color& other) const {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        bool operator!=(const Color& other) const {
            return !(*this == other);
        }

        static Color Black() {
            return Color(0, 0, 0);
        }

        static Color White() {
            return Color(255, 255, 255);
        }

        static Color Red() {
            return Color(255, 0, 0);
        }

        static Color Green() {
            return Color(0, 255, 0);
        }

        static Color Blue() {
            return Color(0, 0, 255);
        }

        static Color Yellow() {
            return Color(255, 255, 0);
        }

        static Color Magenta() {
            return Color(255, 0, 255);
        }

        static Color Cyan() {
            return Color(0, 255, 255);
        }

        static Color Transparent() {
            return Color(0, 0, 0, 0);
        }

        SDL_Color toSDL_Color() {
            return SDL_Color{r, g, b, a};
        }
    };
}

#endif //APPLICATION_COLOR_H

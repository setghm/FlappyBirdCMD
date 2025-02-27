#pragma once

#include <cinttypes>
#include <vector>
#include <functional>

typedef std::function<void(void)> VoidCallback;

struct Rect2d;
struct Vector2d;
struct Size2d;
enum class Color : uint8_t;
struct ColorData;
struct CollisionMask;

struct Rect2d {
	double x;
	double y;
	double width;
	double height;
};

struct Vector2 {
	double x;
	double y;

    /*
    * Calculate the dot product.
    */
    double dot(const Vector2& other) const {
        return x * x + y * other.y;
    }
};

struct Size2d {
    uint32_t width;
    uint32_t height;
};

struct ColorData {
    std::vector<uint8_t> colors;

    Size2d size;

    Color color_key;
};

enum class Color : uint8_t {
    undefined = 0,
    black = 0x0F,  // Black background, bright white text
    blue = 0x1F,  // Blue background, bright white text
    green = 0x2F,  // Green background, bright white text
    aqua = 0x3F,  // Aqua background, bright white text
    red = 0x4F,  // Red background, bright white text
    purple = 0x5F,  // Purple background, bright white text
    yellow = 0x6F,  // Yellow background, bright white text
    white = 0x7F,  // White background, black text
    gray = 0x8F,  // Gray background, black text
    bright_blue = 0x9F,  // Bright blue background, black text
    bright_green = 0xAF,  // Bright green background, black text
    bright_aqua = 0xBF,  // Bright aqua background, black text
    bright_red = 0xCF,  // Bright red background, black text
    bright_purple = 0xDF, // Bright purple background, black text
    bright_yellow = 0xEF, // Bright yellow background, black text
    bright_white = 0x0F  // Bright white background, black text
};

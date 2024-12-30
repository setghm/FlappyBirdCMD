#pragma once

#include "Types.hpp"

enum class InputEventType {
    keyboard,
    mouse
};

class InputEvent {
public:
    InputEvent(InputEventType type) : type(type) {}

    InputEventType type;
};

class KeyboardEvent : public InputEvent {
public:
    KeyboardEvent() : InputEvent(InputEventType::keyboard) {
        keycode = 0;
        is_pressed = false;
    }

    int keycode;
    bool is_pressed;
};

enum class MouseButton {
    left,
    right,
    other
};

class MouseEvent : public InputEvent {
public:
    MouseEvent() : InputEvent(InputEventType::mouse) {
        position = { 0 };
        button = MouseButton::other;
        is_pressed = false;
    }

    Vector2 position;
    MouseButton button;
    bool is_pressed;
};

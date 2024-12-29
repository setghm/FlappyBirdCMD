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
    KeyboardEvent() : InputEvent(InputEventType::keyboard) {}

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
    MouseEvent() : InputEvent(InputEventType::mouse) {}

    Vector2 position;
    MouseButton button;
    bool is_pressed;
};

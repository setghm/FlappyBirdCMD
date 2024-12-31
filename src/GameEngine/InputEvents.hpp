#pragma once

#include "Types.hpp"

enum class InputEventType {
    keyboard,
    mouse
};

class KeyboardEvent;
class MouseEvent;

class InputEvent {
public:
    InputEvent(InputEventType type) : type(type) {}

    InputEventType type;

    bool isKeyboardEvent(void) const { return type == InputEventType::keyboard; }

    bool isMouseEvent(void) const { return type == InputEventType::mouse; }

    const KeyboardEvent* toKeyboardEvent(void) const { return (KeyboardEvent*)(this); }

    const MouseEvent* toMouseEvent(void) const { return (MouseEvent*)this; }
};

class KeyboardEvent : public InputEvent {
public:
    KeyboardEvent() : InputEvent(InputEventType::keyboard) {
        keycode = 0;
        is_pressed = false;
    }

    int keycode;
    bool is_pressed;

    bool anyKeyPressed(void) const { return is_pressed; }
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

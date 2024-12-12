#pragma once
#include <array>

#include "allegro5/allegro.h"

#include "Math/Vector.hpp"

#include "Debug/Log.hpp"

// pressed: if the button is pressed down
// released: if the button is not pressed down
// buttondown: if the button has just been clicked
// buttonup: if the button has just been released
struct MouseState {
	bool pressed;
	bool released;
	bool buttondown;
	bool buttonup;
};

class Mouse {
public:
	// Copied from allegro
	enum MouseCode {
		LEFT = 0,
		RIGHT = 1,
		MIDDLE = 2,
		BUTTON_MAX
	};
	Mouse() = delete;

	// Set all key states to the intiailzie state
	// (pressed = 0, released = 0, buttondown = 0, buttonup = 0)
	static void initialize();

	// Update all the button states
	static void update();

	// Returns a button state of a certain mouse code
	static MouseState get(MouseCode code);

	// Returns the current mouse position
	static const vec2& getPosition();

	// Returns how much the mouse has moved since last frame
	static vec2 getDeltaPosition();

	static int getScroll();
private:
	static std::array<MouseState, MouseCode::BUTTON_MAX> s_states;
	static std::array<MouseState, MouseCode::BUTTON_MAX> s_lastStates;
	static vec2 s_position;
	static vec2 s_lastPosition;
	static vec2 s_deltaPosition;
	static int s_scroll;
	static int s_lastScroll;
};
#pragma once
#include <array>

#include "allegro5/allegro.h"

#include "Math/Vector.hpp"

struct MouseState {
	bool pressed;
	bool released;
	bool buttondown;
	bool buttonup;
};

class Mouse {
public:
	enum MouseCode {
		LEFT = 0,
		RIGHT = 1,
		MIDDLE = 2,
		BUTTON_MAX
	};
	Mouse() = delete;

	static void initialize();
	static void update();

	static MouseState get(MouseCode code);
	static const vec2& getPosition();
	static vec2 getDeltaPosition();
private:
	static std::array<MouseState, MouseCode::BUTTON_MAX> s_states;
	static std::array<MouseState, MouseCode::BUTTON_MAX> s_lastStates;
	static vec2 s_position;
	static vec2 s_lastPosition;
	static vec2 s_deltaPosition;
};
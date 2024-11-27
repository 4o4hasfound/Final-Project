#include "Engine/Mouse.hpp"

std::array<MouseState, Mouse::BUTTON_MAX> Mouse::s_states;
std::array<MouseState, Mouse::BUTTON_MAX> Mouse::s_lastStates;
vec2 Mouse::s_position;
vec2 Mouse::s_lastPosition;
vec2 Mouse::s_deltaPosition;

void Mouse::initialize() {
	for (auto& state : s_states) {
		state.pressed = 0;
		state.released = 1;
		state.buttondown = 0;
		state.buttonup = 0;
	}
	s_lastStates = s_states;
	s_position = s_lastPosition = vec2(0);
}

void Mouse::update() {
	s_lastStates = s_states;
	s_lastPosition = s_position;
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	for (int i = 0; i < s_states.size(); ++i) {
		s_states[i].pressed = al_mouse_button_down(&state, i + 1);
		s_states[i].released = !s_states[i].pressed;
		s_states[i].buttondown = s_lastStates[i].released && s_states[i].pressed;
		s_states[i].buttonup = s_lastStates[i].pressed && s_states[i].released;
	}
	s_position.x = state.x;
	s_position.y = state.y;
}

MouseState Mouse::get(MouseCode code) {
	return s_states[code];
}

const vec2& Mouse::getPosition() {
	return s_position;
}

vec2 Mouse::getDeltaPosition() {
	return s_position - s_lastPosition;
}

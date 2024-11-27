#include "Engine/Keyboard.hpp"

std::array<KeyState, Keyboard::KEY_MAX> Keyboard::s_states;
std::array<KeyState, Keyboard::KEY_MAX> Keyboard::s_lastStates;

void Keyboard::initialize() {
	for (auto& state : s_states) {
		state.pressed = 0;
		state.released = 1;
		state.keydown = 0;
		state.keyup = 0;
	}
	s_lastStates = s_states;
}

void Keyboard::update() {
	s_lastStates = s_states;
	ALLEGRO_KEYBOARD_STATE state;
	al_get_keyboard_state(&state);
	for (int i = 0; i < s_states.size(); ++i) {
		s_states[i].pressed = al_key_down(&state, i + 1);
		s_states[i].released = !s_states[i].pressed;
		s_states[i].keydown = s_lastStates[i].released && s_states[i].pressed;
		s_states[i].keyup = s_lastStates[i].pressed && s_states[i].released;
	}
}

KeyState Keyboard::get(KeyCode code) {
	return s_states[code];
}

#pragma once

template<typename StateType, typename ...T, typename>
State* StateManager::makeState(const T&... t) {
	return new StateType(this, t...);
}
template<typename StateType, typename ...T, typename>
State* StateManager::emplaceState(const T&... t) {
	State* state = new StateType(this, t...);
	pushState(state);
	return state;
}
template<typename StateType, typename ...T, typename>
State* StateManager::emplaceSwitchState(const T&... t) {
	State* state = new StateType(this, t...);
	switchState(state);
	return state;
}
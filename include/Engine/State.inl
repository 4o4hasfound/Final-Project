#pragma once

template<typename StateType, typename ...T, typename>
State* StateManager::makeState(T&... t) {
	return new StateType(*this, t...);
}
template<typename StateType, typename ...T, typename>
State* StateManager::emplaceState(T&... t) {
	State* state = new StateType(*this, t...);
	pushState(state);
	return state;
}
template<typename StateType, typename ...T, typename>
State* StateManager::emplaceSwitchState(T&... t) {
	State* state = new StateType(*this, t...);
	switchState(state);
	return state;
}
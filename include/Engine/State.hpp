#pragma once
#include <stack>

class State;

class StateManager {
public:
	StateManager();
	~StateManager();

	void pushState(State* state);
	State* topState();
	void popState(int n);
	void switchState(State* state);

	void update();
	
	template<typename StateType, typename ...T, typename = std::enable_if_t<std::is_base_of_v<State, StateType>>>
	State* makeState(const T&... t);
	template<typename StateType, typename ...T, typename = std::enable_if_t<std::is_base_of_v<State, StateType>>>
	State* emplaceState(const T&... t);
	template<typename StateType, typename ...T, typename = std::enable_if_t<std::is_base_of_v<State, StateType>>>
	State* emplaceSwitchState(const T&... t);
private:
	std::stack<State*> m_states;
	std::stack<State*> m_toRemove;
};

class State {
public:
	State(StateManager& manager);

	virtual void OnEnter() {};
	virtual void OnDestroy() {};
	virtual void OnSuspend() {};
	virtual void OnWakeup() {};
protected:
	StateManager& m_manager;
};

#include "Engine/State.inl"
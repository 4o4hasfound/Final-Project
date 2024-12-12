#pragma once
#include <stack>

#include "Render/RenderWindow.hpp"

class State;

class StateManager {
public:
	StateManager();
	~StateManager();

	bool empty() const;
	int size() const;

	// Pushes a new state onto the stack
	void pushState(State* state);

	// Retrieves the state currently on top of the stack
	State* topState();

	// Retrieves the nth state of the stack
	State* nthState(int n);

	// Pops one or more states from the stack
	void popState(int n);

	// Replaces the current state with a new state
	void switchState(State* state);

	// This function can be called each frame to update the current state
	// and clean up the removed states
	void update();

	// Creates a new state using the specified constructor arguments
	template<typename StateType, typename ...T, typename = std::enable_if_t<std::is_base_of_v<State, StateType>>>
	State* makeState(T... t);

	// Creates a new state using the specified constructor arguments
	// then push it onto the stack
	template<typename StateType, typename ...T, typename = std::enable_if_t<std::is_base_of_v<State, StateType>>>
	State* emplaceState(T... t);

	// Replaces the current state with a newly created state
	template<typename StateType, typename ...T, typename = std::enable_if_t<std::is_base_of_v<State, StateType>>>
	State* emplaceSwitchState(T... t);
private:
	std::vector<State*> m_states;
	std::vector<State*> m_toRemove;
};

class State {
	friend class StateManager;
public:
	State(StateManager& manager);

	// Called when the state is entered
	virtual void onEnter() {};

	// Called when the state is destroyed
	virtual void onDestroy() {};

	// Called when the state is suspended(another state is pushed on top of it)
	virtual void onSuspend() {};

	// Called when the state is resumed after suspension
	virtual void onWakeup() {};

	virtual void reset() {};
	virtual void update(RenderWindow& window, float dt) {};
	virtual void render(RenderWindow& window) {};
	virtual bool shouldClose() = 0;
protected:
	StateManager& m_manager;
	bool m_removed = 0;
};

#include "Engine/State.inl"
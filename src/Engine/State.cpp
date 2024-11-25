#include "Engine/State.hpp"

StateManager::StateManager() {

}

StateManager::~StateManager() {
	while (!m_states.empty()) {
		delete m_states.top();
		m_states.pop();
	}
	while (!m_toRemove.empty()) {
		delete m_toRemove.top();
		m_toRemove.pop();
	}
}

void StateManager::pushState(State* state) {
	state->OnEnter();
	if (!m_states.empty()) {
		m_states.top()->OnSuspend();
	}
	m_states.push(state);
}

State* StateManager::topState() {
	return m_states.top();
}

void StateManager::popState(int n) {
	while (n-- && !m_states.empty()) {
		m_states.top()->OnDestroy();
		m_toRemove.push(m_states.top());
		m_states.pop();
	}
	if (!m_states.empty()) {
		m_states.top()->OnWakeup();
	}
}

void StateManager::switchState(State* state) {
	m_states.top()->OnDestroy();
	m_toRemove.push(m_states.top());
	m_states.pop();

	state->OnEnter();
	m_states.push(state);
}

void StateManager::update() {
	while (!m_toRemove.empty()) {
		delete m_toRemove.top();
		m_toRemove.pop();
	}
}

State::State(StateManager& manager)
	: m_manager(manager) {

}

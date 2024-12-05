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

bool StateManager::empty() const {
	return m_states.empty();
}

int StateManager::size() const {
	return m_states.size();
}

void StateManager::pushState(State* state) {
	state->onEnter();
	if (!m_states.empty()) {
		m_states.top()->onSuspend();
	}
	m_states.push(state);
}

State* StateManager::topState() {
	if (m_states.empty()) {
		return nullptr;
	}
	return m_states.top();
}

void StateManager::popState(int n) {
	while (n-- && !m_states.empty()) {
		m_states.top()->onDestroy();
		m_toRemove.push(m_states.top());
		m_states.pop();
	}
	if (!m_states.empty()) {
		m_states.top()->onWakeup();
	}
}

void StateManager::switchState(State* state) {
	m_states.top()->onDestroy();
	m_toRemove.push(m_states.top());
	m_states.pop();

	state->onEnter();
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

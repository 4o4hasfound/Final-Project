#include "Engine/State.hpp"

StateManager::StateManager() {

}

StateManager::~StateManager() {
	while (!m_states.empty()) {
		delete m_states.back();
		m_states.pop_back();
	}
	while (!m_toRemove.empty()) {
		delete m_toRemove.back();
		m_toRemove.pop_back();
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
		m_states.back()->onSuspend();
	}
	m_states.push_back(state);
}

State* StateManager::topState() {
	if (m_states.empty()) {
		return nullptr;
	}
	return m_states.back();
}

State* StateManager::nthState(int n) {
	if (m_states.size() <= n) {
		return nullptr;
	}
	return m_states[m_states.size() - 1 - n];
}

void StateManager::popState(int n) {
	while (n-- && !m_states.empty()) {
		m_states.back()->onDestroy();
		m_states.back()->m_removed = true;
		m_toRemove.push_back(m_states.back());
		m_states.pop_back();
	}
	if (!m_states.empty()) {
		m_states.back()->onWakeup();
	}
}

void StateManager::switchState(State* state) {
	m_states.back()->onDestroy();
	m_states.back()->m_removed = true;
	m_toRemove.push_back(m_states.back());
	m_states.pop_back();

	state->onEnter();
	m_states.push_back(state);
}

void StateManager::update() {
	while (!m_toRemove.empty()) {
		delete m_toRemove.back();
		m_toRemove.pop_back();
	}
}

State::State(StateManager& manager)
	: m_manager(manager) {

}

bool State::shouldClose() {
	return m_shouldClose;
}

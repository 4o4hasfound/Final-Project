#include "Engine/Engine.hpp"
#include "Game/States/TestState.hpp"

int main() {
	Engine::init();

	Engine::states.emplaceState<TestState>(*(Engine::window));
	Engine::run();

	Engine::terminate();
}
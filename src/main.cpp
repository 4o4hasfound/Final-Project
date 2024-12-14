#include "Engine/Engine.hpp"
#include "Game/States/TestState.hpp"
#include "Game/States/MenuState.hpp"

int main() {
	Engine::init();

	Engine::states.emplaceState<MenuState>(Engine::window);
	Engine::run();

	Engine::terminate();
}
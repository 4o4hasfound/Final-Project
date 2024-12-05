#include "Engine/Engine.hpp"

bool Engine::initialized = 0;
RenderWindow* Engine::window;
Clock Engine::deltaTime;
StateManager Engine::states;

void Engine::init() {
	if (initialized) {
		return;
	}
	initialized = 1;

	al_init();
	al_install_mouse();
	al_install_keyboard();
	al_install_audio();
	al_reserve_samples(50);

	if (!al_init_acodec_addon()) {
		Logger::Log<Error>("Failed to initialize allegro acodec addon");
	}

	if (!al_init_font_addon()) {
		Logger::Log<Error>("Failed to initialize allegro font addon");
	}

	if (!al_init_image_addon()) {
		Logger::Log<Error>("Failed to initialize allegro image addon");
	}

	if (!al_init_primitives_addon()) {
		Logger::Log<Error>("Failed to initialize allegro primitive addon");
	}

	if (!al_init_video_addon()) {
		Logger::Log<Error>("Failed to initialize allegro video addon");
	}

	Mouse::initialize();
	Keyboard::initialize();

	// You can comment this out if threading aren't used
	ThreadPool::launch(24);

	window = new RenderWindow(1920, 1080, "Game");
}

void Engine::terminate() {
	ThreadPool::terminate();
	delete window;
}

void Engine::run() {
	deltaTime.reset();

	while (window->running()) {
		Engine::update();

		window->pollEvents();
		window->clear();

		State* state = states.topState();
		if (!state || state->shouldClose()) {
			break;
		}

		state->update(*window, deltaTime.reset());
		state->render(*window);


		window->flipDisplay();
	}
}

void Engine::update() {
	Mouse::update();
	Keyboard::update();
}

#include "Engine/Engine.hpp"
bool Engine::initialized = 0;

void Engine::init() {
	if (initialized) {
		return;
	}
	initialized = 1;

	al_init();
	al_install_mouse();
	al_install_keyboard();
	al_install_audio();
	al_reserve_samples(20);

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
}

void Engine::terminate() {
	ThreadPool::terminate();
}

void Engine::update() {
	Mouse::update();
	Keyboard::update();
}

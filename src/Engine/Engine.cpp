#include "Engine/Engine.hpp"
bool Engine::initialized = 0;

void Engine::Init() {
	if (initialized) {
		return;
	}
	initialized = 1;

	al_init();

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

	ThreadPool::Launch(24);
}

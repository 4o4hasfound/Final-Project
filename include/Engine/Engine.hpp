#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_ttf.h>

#include "Utils/ThreadPool.hpp"

#include "Engine/Keyboard.hpp"
#include "Engine/Mouse.hpp"
#include "Engine/State.hpp"
#include "Engine/Audio.hpp"

#include "Render/RenderWindow.hpp"
#include "Render/Texture.hpp"

#include "Utils/Clock.hpp"

#include "Debug/Log.hpp"

class Engine {
public:
	// Call this function at the very beginning of the propgram
	// This handles the initialization of:
	// 1. allegro
	// 2. allegro plugins
	// 3. Keyboard
	// 4. Mouse
	// 5. ThreadPool
	static void init();

	// Call this function at the very end of the program
	static void terminate();

	// Run the main loop
	static void run();

	static RenderWindow* window;
	static StateManager states;
private:
	Engine() = delete;

	// Call this function at every frame
	static void update();

	static bool initialized;
	static Clock deltaTime;
};
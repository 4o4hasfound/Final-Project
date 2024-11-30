#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_video.h>

#include "Utils/ThreadPool.hpp"

#include "Engine/Keyboard.hpp"
#include "Engine/Mouse.hpp"

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

	// Call this function at every frame
	static void update();
private:
	Engine() = delete;
	
	static bool initialized;
};
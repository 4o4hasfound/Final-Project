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

#include "Debug/Log.hpp"

class Engine {
public:
	static void Init();
	//static void Run();
private:
	Engine() = delete;
	
	static bool initialized;
};
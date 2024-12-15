#pragma once
#include <string>
#include <vector>

#define ALLEGRO_UNSTABLE
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Container/FreeList.hpp"

#include "Debug/Log.hpp"

class Audio {
public:
	// Copied from allegro
	enum PlayMode {
		ONCE = 0x100,
		LOOP = 0x101,
		BIDIR = 0x102,
		LOOPONCE = 0x105
	};
	Audio();
	Audio(const std::string& filename);
	~Audio();

	void load(const std::string& filename);

	void play(float speed, float sound = 1.0);
	bool playing();

	void stop(float fadeoutSpeed = -1.0);

	static void update(float dt);
	static void stopAll(float fadeoutSpeed = -1.0);

	ALLEGRO_SAMPLE* sample;
	FreeList<ALLEGRO_SAMPLE_ID> ids;
private:
	struct ToDeleteSample {
		ALLEGRO_SAMPLE_ID id;
		float fadeoutSpeed;

		ToDeleteSample(ALLEGRO_SAMPLE_ID _id, float speed) 
			: id(_id), fadeoutSpeed(speed) {}
	};
	static FreeList<ALLEGRO_SAMPLE_ID> s_globalIDs;
	static FreeList<ToDeleteSample> s_toDeleteIds;
};
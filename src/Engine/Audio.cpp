#include "Engine/Audio.hpp"

Audio::Audio()
	: sample(nullptr) {

}

Audio::Audio(const std::string& filename)
	: sample(al_load_sample(filename.c_str())) {
	if (!sample) {
		Logger::Log<Debug>("Cannot load audio sample from file:", filename);
	}
}

Audio::~Audio() {
	al_destroy_sample(sample);
}

void Audio::load(const std::string& filename) {
	if (sample) {
		al_destroy_sample(sample);
	}
	sample = al_load_sample(filename.c_str());
	if (!sample) {
		Logger::Log<Debug>("Cannot load audio sample from file:", filename);
	}
}

void Audio::play(float speed, float sound) {
	for (auto itr = ids.begin(), end = ids.end(); itr != end; ++itr) {
		ALLEGRO_SAMPLE_ID id = *itr;
		ALLEGRO_SAMPLE_INSTANCE* instance = al_lock_sample_id(&id);

		if (!instance || !al_get_sample_instance_playing(instance)) {
			ids.remove(itr);
		}
		al_unlock_sample_id(&id);
	}
	ALLEGRO_SAMPLE_ID id;
	al_play_sample(sample, sound, 0.0, speed, ALLEGRO_PLAYMODE_ONCE, &id);
	ids.push(id);
}

bool Audio::playing() {
	for (auto itr = ids.begin(), end = ids.end(); itr != end; ++itr) {
		ALLEGRO_SAMPLE_ID id = *itr;
		ALLEGRO_SAMPLE_INSTANCE* instance = al_lock_sample_id(&id);
		if (!instance || !al_get_sample_instance_playing(instance)) {
			ids.remove(itr);
		}
		al_unlock_sample_id(&id);
	}
	return !ids.empty();
}

void Audio::stop() {
	for (auto itr = ids.begin(), end = ids.end(); itr != end; ++itr) {
		ALLEGRO_SAMPLE_ID id = *itr;
		ALLEGRO_SAMPLE_INSTANCE* instance = al_lock_sample_id(&id);

		if (instance) {
			al_stop_sample_instance(instance);
			al_unlock_sample_id(&id);
		}
	}
	ids.clear();
}

void Audio::stopAll() {
	al_stop_samples();
}

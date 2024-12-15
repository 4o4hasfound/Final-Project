#include "Engine/Audio.hpp"

FreeList<ALLEGRO_SAMPLE_ID> Audio::s_globalIDs;
FreeList<Audio::ToDeleteSample> Audio::s_toDeleteIds;

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
	s_globalIDs.push(id);
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

void Audio::stop(float fadeoutSpeed) {
	for (auto itr = ids.begin(), end = ids.end(); itr != end; ++itr) {
		ALLEGRO_SAMPLE_ID id = *itr;
		ALLEGRO_SAMPLE_INSTANCE* instance = al_lock_sample_id(&id);

		if (instance) {
			if (fadeoutSpeed == -1) {
				al_stop_sample_instance(instance);
			}
			else {
				s_toDeleteIds.emplace(id, fadeoutSpeed);
			}
		}
	}
	ids.clear();
}

void Audio::update(float dt) {
	for (auto itr = s_globalIDs.begin(), end = s_globalIDs.end(); itr != end; ++itr) {
		ALLEGRO_SAMPLE_ID id = *itr;
		ALLEGRO_SAMPLE_INSTANCE* instance = al_lock_sample_id(&id);

		if (!instance || !al_get_sample_instance_playing(instance)) {
			s_globalIDs.remove(itr);
		}
		al_unlock_sample_id(&id);
	}
	for (auto itr = s_toDeleteIds.begin(), end = s_toDeleteIds.end(); itr != end; ++itr) {
		ALLEGRO_SAMPLE_ID id = itr->id;
		ALLEGRO_SAMPLE_INSTANCE* instance = al_lock_sample_id(&id);

		if (!instance) {
			s_toDeleteIds.remove(itr);
			continue;
		}

		float gain = al_get_sample_instance_gain(instance);

		if (gain - dt * itr->fadeoutSpeed <= 0) {
			al_stop_sample_instance(instance);
		}
		else {
			al_set_sample_instance_gain(instance, gain * (1.0 - dt * itr->fadeoutSpeed));
		}
	}
}

void Audio::stopAll(float fadeoutSpeed) {
	for (auto itr = s_globalIDs.begin(), end = s_globalIDs.end(); itr != end; ++itr) {
		ALLEGRO_SAMPLE_ID id = *itr;
		ALLEGRO_SAMPLE_INSTANCE* instance = al_lock_sample_id(&id);

		if (!instance || !al_get_sample_instance_playing(instance)) {
			if (fadeoutSpeed == -1) {
				al_stop_sample_instance(instance);
			}
			else {
				s_toDeleteIds.emplace(id, fadeoutSpeed);
			}
		}
		al_unlock_sample_id(&id);
	}
	s_globalIDs.clear();
}

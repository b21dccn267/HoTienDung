#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class SoundManager
{
public:
	SoundManager(const SoundManager& instance) = delete;
	static SoundManager* instance;
	static SoundManager* GetInstance() {
		if (!instance)
		{
			instance = new SoundManager();
		}
		return instance;
	}
	static void DestroyInstance() {
		delete instance;
		instance = nullptr;
	}

	void Init();
	static void PlaySound(const char* fileName);
	static void PlaySfx(const char* fileName);
	static void UpdateSound();
private:
	SoundManager() {};
};


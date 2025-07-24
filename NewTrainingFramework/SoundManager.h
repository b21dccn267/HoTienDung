#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class SoundManager
{
public:
	SoundManager();
	static void PlaySound(const char* fileName);
	static void PlaySfx(const char* fileName);
	static void UpdateSound();
};


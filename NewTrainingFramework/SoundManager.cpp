#include "stdafx.h"
#include "SoundManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

SoundManager::SoundManager()
{
	SDL_Init(SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);

	Mix_AllocateChannels(16);
}

void SoundManager::PlaySound(const char* fileName)
{
	Mix_LoadMUS(fileName);
}

void SoundManager::PlaySfx(const char* fileName)
{
	Mix_LoadWAV(fileName);
}

void SoundManager::UpdateSound()
{
}

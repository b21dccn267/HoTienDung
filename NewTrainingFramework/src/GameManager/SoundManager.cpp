#include "SoundManager.h"
#include "../../../Include/SDL2/SDL.h"
#include "../../../Include/SDL2/SDL_mixer.h"
#include <cstdio>


SoundManager* SoundManager::instance = nullptr;

void SoundManager::Init()
{
	if (SDL_Init(SDL_INIT_AUDIO) == 0) {
		printf("thing works\n");
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) == 0) {
		printf("thing works\n");
	}

	//const SDL_version* version = Mix_Linked_Version();

	Mix_AllocateChannels(16);

	//Mix_Chunk* test = Mix_LoadWAV("../Resources/Sfx/vine-boom.wav");

	//Mix_PlayChannel(-1, test, -1);
}

// should use channel 1, play on loop
void SoundManager::PlaySound(const char* fileName)
{
	//Mix_LoadMUS(fileName);
	//Mix_PlayChannel(1, Mix_LoadMUS(fileName), 4);
}

// should use channel 2
void SoundManager::PlaySfx(const char* fileName)
{
	Mix_LoadWAV(fileName);
	//Mix_PlayChannel(2, Mix_LoadMUS(fileName), 4);
}

void SoundManager::UpdateSound()
{
}

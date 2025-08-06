#pragma once
#include "../Utilities/utilities.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class Texture
{
public:
	GLuint textureId;

	// merge all texture func
	Texture(const char* fileName, int param);
	Texture(SDL_Surface* surface);
	~Texture();
};


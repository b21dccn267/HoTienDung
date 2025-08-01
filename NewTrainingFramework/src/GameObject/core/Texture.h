#pragma once
#include "../../../../Include/SDL2/SDL.h"
#include "../../../../Include/SDL2/SDL_ttf.h"
#include "../../../../Utilities/utilities.h"

class Texture
{
public:
	GLuint textureId;

	// merge all texture func
	Texture(const char* fileName, int param);
	Texture(SDL_Surface* surface);
	~Texture();
};


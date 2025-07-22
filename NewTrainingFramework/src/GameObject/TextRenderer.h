#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// this class creates texture from text for objects
class TextRenderer
{
public:
	static SDL_Surface* FlipVertical(SDL_Surface* surface);
	static SDL_Surface* RenderText(const char* text); // add font option later
};


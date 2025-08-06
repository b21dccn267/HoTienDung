#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class TextRenderer
{
public:
	static SDL_Surface* FlipVertical(SDL_Surface* surface);

	// Basic text rendering with default font and color
	static SDL_Surface* RenderText(const char* text);

	// Text rendering with custom font and size
	static SDL_Surface* RenderText(const char* text, const char* fontPath, int fontSize);

	// Text rendering with custom font, size, and color
	static SDL_Surface* RenderText(const char* text, const char* fontPath, int fontSize, SDL_Color color);
};
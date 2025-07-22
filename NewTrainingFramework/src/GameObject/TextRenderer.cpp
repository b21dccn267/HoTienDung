#include "stdafx.h"
#include "TextRenderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Utilities/utilities.h"

SDL_Surface* TextRenderer::FlipVertical(SDL_Surface* surface)
{
	if (!surface || surface->format->BitsPerPixel != 32) {
		return nullptr;
	}

	SDL_Surface* result = SDL_CreateRGBSurfaceWithFormat(
		0,
		surface->w,
		surface->h,
		surface->format->BitsPerPixel,
		surface->format->format
	);
	if (!result) {
		return nullptr;
	}

	SDL_Rect sRect = { 0, 0, surface->w, 1 };
	SDL_Rect rRect = { 0, 0, result->w, 1 };

	for (int y = 0; y < surface->h; y++) {
		sRect.y = y;
		rRect.y = surface->h - 1 - y;
		SDL_BlitSurface(surface, &sRect, result, &rRect);
	}

	SDL_FreeSurface(surface);
	return result;
}

// suggested changes:
// make this class a CC of Object minus texture
// chosen changes:
// have this class only poops out SDL_Surface
// then add a new Texture ctor for it
SDL_Surface* TextRenderer::RenderText(const char* text)
{
	if (TTF_Init() != 0) {
		printf("thing broke\n");
	}
	TTF_Font* font = TTF_OpenFont("../Resources/Fonts/Roboto-VariableFont_wdth,wght.ttf", 24);
	if (!font) {
		printf("thing broke\n");
	}

	const char* message = "something meaningful";
	SDL_Color white = { 255, 255, 255, 255 };

	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, message, white);
	if (!surface) {
		printf("thing broke\n");
	}

	SDL_Surface* result = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
	SDL_FreeSurface(surface);
	SDL_Surface* flippedResult = FlipVertical(result);
	SDL_FreeSurface(result);


	//return result;
	//return FlipVertical(result);
	return flippedResult;
}

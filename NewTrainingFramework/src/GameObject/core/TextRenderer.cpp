#include "../Utilities/utilities.h"
#include "TextRenderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

// Basic text rendering với default font và color
SDL_Surface* TextRenderer::RenderText(const char* text)
{
	if (TTF_Init() != 0) {
		return nullptr;
	}

	TTF_Font* font = TTF_OpenFont("../Resources/Fonts/ChangaOne-Regular.ttf", 24);
	if (!font) {
		return nullptr;
	}

	SDL_Color whiteColor = { 255, 255, 255, 255 };

	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, whiteColor);
	if (!surface) {
		TTF_CloseFont(font);
		return nullptr;
	}

	SDL_Surface* result = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
	SDL_FreeSurface(surface);

	if (!result) {
		TTF_CloseFont(font);
		return nullptr;
	}

	SDL_Surface* flippedResult = FlipVertical(result);

	TTF_CloseFont(font);
	return flippedResult;
}

// Text rendering với custom font size
SDL_Surface* TextRenderer::RenderText(const char* text, int fontSize)
{
	if (TTF_Init() != 0) {
		return nullptr;
	}

	TTF_Font* font = TTF_OpenFont("../Resources/Fonts/ChangaOne-Regular.ttf", fontSize);
	if (!font) {
		return nullptr;
	}

	SDL_Color whiteColor = { 255, 255, 255, 255 };

	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, whiteColor);
	if (!surface) {
		TTF_CloseFont(font);
		return nullptr;
	}

	SDL_Surface* result = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
	SDL_FreeSurface(surface);

	if (!result) {
		TTF_CloseFont(font);
		return nullptr;
	}

	SDL_Surface* flippedResult = FlipVertical(result);

	TTF_CloseFont(font);
	return flippedResult;
}

// Text rendering với custom font path và size (không có color)
SDL_Surface* TextRenderer::RenderText(const char* text, const char* fontPath, int fontSize)
{
	SDL_Color whiteColor = { 255, 255, 255, 255 };
	return RenderText(text, fontPath, fontSize, whiteColor);
}

// Text rendering với custom font, size, và color
SDL_Surface* TextRenderer::RenderText(const char* text, const char* fontPath, int fontSize, SDL_Color color)
{
	if (TTF_Init() != 0) {
		return nullptr;
	}

	TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
	if (!font) {
		return nullptr;
	}

	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
	if (!surface) {
		TTF_CloseFont(font);
		return nullptr;
	}

	SDL_Surface* result = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
	SDL_FreeSurface(surface);

	if (!result) {
		TTF_CloseFont(font);
		return nullptr;
	}

	SDL_Surface* flippedResult = FlipVertical(result);

	TTF_CloseFont(font);
	return flippedResult;
}
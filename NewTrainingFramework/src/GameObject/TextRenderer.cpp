#include "stdafx.h"
#include "TextRenderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Utilities/utilities.h"

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

	// debug vars
	//SDL_PixelFormatEnum fmt = surface->format->format;
	int bpp = surface->format->BytesPerPixel;
	Uint32 Rmask = surface->format->Rmask;
	Uint32 Gmask = surface->format->Gmask;
	Uint32 Bmask = surface->format->Bmask;
	Uint32 Amask = surface->format->Amask;
	/// convert surface vowis format RGBA



	// no need
	//SDL_Renderer* renderer;
	//SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	//SDL_FreeSurface(surface);
	//if (!texture) {
	//	return;
	//}

	// try to convert this to Texture
	// or do it right here

	//glGenTextures(1, &textureId);
	//glBindTexture(GL_TEXTURE_2D, textureId);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return surface;
}
//void TextRenderer::Draw()
//{
//	//trucj Y nguocj
//}

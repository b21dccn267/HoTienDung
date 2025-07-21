#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// this class creates texture from text for objects
class TextRenderer
{
public:
	//TextRenderer(const TextRenderer& instance) = delete;
	//static TextRenderer* instance;
	//static TextRenderer* GetInstance() {
	//	if (!instance)
	//	{
	//		instance = new TextRenderer();
	//	}
	//	return instance;
	//}

	//static void DestroyInstance() {
	//	delete instance;
	//	instance = nullptr;
	//}

	static SDL_Surface* RenderText(const char* text); // add font option later
};


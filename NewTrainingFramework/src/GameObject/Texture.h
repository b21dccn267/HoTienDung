#pragma once
#include "../Utilities/utilities.h"

class Texture
{
public:
	GLuint textureId;

	// merge all texture func
	Texture(const char* fileName, int param);
	~Texture();
};


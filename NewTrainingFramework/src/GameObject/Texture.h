#pragma once
#include "../Utilities/utilities.h"

class Texture
{
public:
	GLuint textureId;
	int iWidth, iHeight, iBdp;
	char* imageData;

	int Init(const char* imageData);
	void SetTextureParameters();
	~Texture();
};


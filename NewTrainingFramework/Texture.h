#pragma once
#include "../Utilities/utilities.h"

class Texture
{
public:
	GLuint textureID;
	float vertices_pos[1] = {1};
	float uv_pos[];


	//int Init();
	void Load(char* imageData);
	~Texture();
};


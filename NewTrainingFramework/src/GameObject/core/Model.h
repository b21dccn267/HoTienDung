#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"


class Model
{
public:	
	GLuint vboId, iboId;
	int numberOfIndex;

	// merge all functions into this
	Model(const char* fileName);
	~Model();
};


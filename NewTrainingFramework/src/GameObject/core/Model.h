#pragma once
#include "../../../../Utilities/utilities.h"
#include "../core/Vertex.h"

class Model
{
public:	
	GLuint vboId, iboId;
	int numberOfIndex;

	// merge all functions into this
	Model(const char* fileName);
	~Model();
};


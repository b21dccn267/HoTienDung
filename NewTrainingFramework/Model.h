#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"

class Model
{
public:	
	FILE* f;
	Vertex* verticesData;
	GLuint* indicesData;
	GLuint vboId, iboId;
	char* modelData;

	
	int Init(const char* modelData);
	void BindBuffer();
	void SetModelParameters();
	~Model();
};


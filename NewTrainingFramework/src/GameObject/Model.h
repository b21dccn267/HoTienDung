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
	int vertexCount, indexCount;

	
	int Init(const char* fileName);
	void BindBuffer();
	void SetModelParameters();
	~Model();
};


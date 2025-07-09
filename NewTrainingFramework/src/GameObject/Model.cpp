#include "stdafx.h"
#include "Model.h"
#include <iostream>


// this function reads data
int Model::Init(const char* fileName) 
{
	f = fopen(fileName, "r");
	
	if (!f) {
		return -1;
	}

	return 0;
}

//this function writes data to NewTrainingFramework.cpp variables
void Model::SetModelParameters()
{
	char line[200];

	fgets(line, sizeof line, f);
	size_t total = strtoul(strchr(line, ':') + 1, nullptr, 10);		// string to size_t the locate chars after ':'
	size_t count = 0;

	sscanf_s(line, "NrVertices: %d", &vertexCount);
	
	verticesData = new Vertex[vertexCount];

	while (count < total && fgets(line, sizeof line, f)) {
		float fX = 0, fY = 0, fZ = 0, fUx = 0, fUy = 0;
		sscanf_s(line, "%*[^p]pos:[%f ,%f ,%f]; %*[^u]uv:[%f ,%f];", &fX, &fY, &fZ, &fUx, &fUy);

		verticesData[count].pos.x = fX;
		verticesData[count].pos.y = fY;
		verticesData[count].pos.z = fZ;
		verticesData[count].uv.x = fUx;
		verticesData[count].uv.y = fUy;

		count++;
	}

	count = 0;
	fgets(line, sizeof line, f);
	total = strtoul(strchr(line, ':') + 1, nullptr, 10);
	sscanf_s(line, "NrIndices: %d", &indexCount);

	indicesData = new GLuint[indexCount];
	
	while (count < total && fgets(line, sizeof line, f)) {
		int iX, iY, iZ;
		sscanf_s(line, "%*d. %d,%d,%d", &iX, &iY, &iZ);

		indicesData[count] = iX; count++;
		indicesData[count] = iY; count++;
		indicesData[count] = iZ; count++;
	}

	fclose(f);
}

void Model::BindBuffer()
{
	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ibo object
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indexCount, indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Model::~Model()
{

}
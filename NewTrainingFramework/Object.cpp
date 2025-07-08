#include "stdafx.h"
#include "Object.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "MVPMatrix.h"

int Object::Init()
{
	const char* modelFileName = "";
	const char* textureFileName = "";
	char* vertexShaderFileName = "";
	char* fragmentShaderFileName = "";

	model->Init(modelFileName);
	texture->Init(textureFileName);
	shader->Init(vertexShaderFileName, fragmentShaderFileName);

	return 0;
}

void Object::ObjectDraw()
{

}
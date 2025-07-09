#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "MVPMatrix.h"

class Object
{
public:
	
	//const char* modelFileName = "";
	//const char* textureFileName = "";
	//char* vertexShaderFileName = "";
	//char* fragmentShaderFileName = "";

	Model* model;
	Texture* texture;
	Shaders* shader;
	MVPMatrix* matrix;

	Object(Model* model, Texture* texture, Shaders* shader, MVPMatrix* matrix);
	int Init(Model* model, Texture* texture, Shaders* shader, MVPMatrix* matrix);
	void Draw();
	void Update();
};


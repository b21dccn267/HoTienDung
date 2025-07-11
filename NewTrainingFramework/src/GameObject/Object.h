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

	Vector3 pos;
	Vector3 rotation;
	Vector3 scale;

	Object(Model* model, Texture* texture, Shaders* shader, Vector3 pos, Vector3 rotation, Vector3 scale); // this is init
	void Draw();
	void Update();
};


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
	Model* model;
	Texture* texture;
	Shaders* shader;
	MVPMatrix matrix;

	int Init();
	void ObjectDraw();
};


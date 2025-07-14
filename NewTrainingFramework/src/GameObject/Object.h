#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"

class Object
{
public:
	Model* model;
	Texture* texture;
	Shaders* shader;

	Vector3 pos;
	Vector3 rotation;
	Vector3 scale;

	Object(Model* model, Texture* texture, Shaders* shader, Vector3 pos, Vector3 rotation, Vector3 scale);
	void WorldMatrix(Matrix world); // model matrix of object
	Matrix CalculateWVP(Matrix modelMatrix, Matrix ViewPerspectiveMatrix); // multiply model matrix with camera matrix
	void Draw(Camera* camera);
	void Update();
};


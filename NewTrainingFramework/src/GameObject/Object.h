#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include <memory>


class Object
{
public:
	//Model* model;
	//Texture* texture;
	//Shaders* shader;
	std::shared_ptr<Model> model;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Shaders> shader;

	Vector3 m_position;
	Vector3 rotation;
	Vector3 m_scale;

	GLint m_iWidth;
	GLint m_iHeight;

	Object();
	//Object(Model* model, Texture* texture, Shaders* shader);
	//Object(Model* model, Texture* texture, Shaders* shader, Vector3 pos, Vector3 rotation, Vector3 scale);
	Object(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader);
	Object(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader, Vector3 pos, Vector3 rotation, Vector3 scale);
	Matrix CalculateWorldMatrix(); // model matrix of object
	Matrix CalculateWVP(Matrix modelMatrix, Matrix ViewPerspectiveMatrix); // multiply model matrix with camera matrix
	void SetSize(GLint width, GLint height);
	void Set2DPosition(Vector2 position);
	void Draw(Camera* camera);
	void Update();
};


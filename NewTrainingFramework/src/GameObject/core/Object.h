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
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Texture> m_pTexture;
	std::shared_ptr<Shaders> m_pShader;

	Vector3 m_position;
	Vector3 rotation;
	Vector3 m_scale;
	Matrix world;
	GLint m_iWidth;
	GLint m_iHeight;
	
	Object();
	Object(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader);
	Object(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader, Vector3 pos, Vector3 rotation, Vector3 scale);

	Matrix CalculateWorldMatrix();
	Matrix CalculateWVP(Matrix modelMatrix, Matrix ViewPerspectiveMatrix);
	void SetSize(GLint width, GLint height);
	void SetRotation(Vector3 rotate);
	void Set2DPosition(Vector2 position);
	void Draw();
	void Update();
	void Update(GLfloat deltaTime);
};


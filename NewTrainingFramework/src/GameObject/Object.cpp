#include "stdafx.h"
#include "Object.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "MVPMatrix.h"
#include "Camera.h"
#include "SceneManager.h"


Object::Object()
{
}

Object::Object(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader)
{
	Object::Object(model, texture, shader, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
}

Object::Object(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader, Vector3 pos, Vector3 rotation, Vector3 scale)
{
	this->model = model;
	this->texture = texture;
	this->shader = shader;
	
	this->m_position = pos;
	this->rotation = rotation;
	this->m_scale = scale;
	CalculateWorldMatrix();
}

Matrix Object::CalculateWorldMatrix()
{
	
	//world.SetIdentity();

	Matrix scaleMatrix, rotationMatrix, translation;

	scaleMatrix.SetScale(m_scale.x, m_scale.y, m_scale.z);

	Matrix rotateX, rotateY, rotateZ;
	rotateX.SetRotationX(rotation.x);
	rotateY.SetRotationY(rotation.y);
	rotateZ.SetRotationZ(rotation.z);
	rotationMatrix = rotateZ * rotateX * rotateY;

	translation.SetTranslation(m_position.x, m_position.y, m_position.z);

	world = scaleMatrix * rotationMatrix * translation;

	return world;
}

Matrix Object::CalculateWVP(Matrix modelMatrix, Matrix ViewPerspectiveMatrix)
{
	return modelMatrix * ViewPerspectiveMatrix;
}

void Object::SetSize(GLint width, GLint height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((GLfloat)m_iWidth, (GLfloat)m_iHeight, 1.0f);
	CalculateWorldMatrix();
}

void Object::Set2DPosition(Vector2 position)
{
	m_position = Vector3(position.x, position.y, 0.0f);
	CalculateWorldMatrix();
}

void Object::Draw()
{
	
//	Matrix matrix = CalculateWorldMatrix();
	//WorldMatrix(matrix);
	//matrix = CalculateWVP(matrix, camera->view * camera->m_perspectiveMatrix);
	//Matrix mvpMatrix = world * SceneManager::GetInstance()->camera->LookAt();
	Matrix mvpMatrix =  world * 
						SceneManager::GetInstance()->camera->m_viewMatrix * 
						SceneManager::GetInstance()->camera->m_perspectiveMatrix;

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	//glDepthMask(GL_TRUE);

	glUseProgram(shader->program);

	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);

	// take location value from vertex/fragment shader. With Position we have location = 0
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	// texture
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}
	int iTextureLoc = glGetUniformLocation(shader->program, "u_texture");
	glUniform1i(iTextureLoc, 0);
	// mvp matrix
	int iMatrixLoc = glGetUniformLocation(shader->program, "u_mvp");
	glUniformMatrix4fv(iMatrixLoc, 1, GL_FALSE, &mvpMatrix.m[0][0]);
	// ibo object
	{
		glDrawElements(GL_TRIANGLES, model->numberOfIndex, GL_UNSIGNED_INT, 0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::Update()
{
	GLfloat deltaTime = 0.1f;
	Vector3 deltaMove = -(m_position - Vector3(0.0f, 0.0f, 0.0f)).Normalize() * deltaTime * SceneManager::GetInstance()->camera->moveSpeed; 

	m_position += deltaMove;
}
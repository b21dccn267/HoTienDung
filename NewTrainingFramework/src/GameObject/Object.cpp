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


Object::Object(Model* model, Texture* texture, Shaders* shader, Vector3 pos, Vector3 rotation, Vector3 scale)
{
	this->model = model;
	this->texture = texture;
	this->shader = shader;
	
	this->pos = pos;
	this->rotation = rotation;
	this->scale = scale;
}

Matrix Object::WorldMatrix()
{
	Matrix world;
	//world.SetIdentity();

	Matrix scaleMatrix, rotationMatrix, translation;

	scaleMatrix.SetScale(scale.x, scale.y, scale.z);

	Matrix rotateX, rotateY, rotateZ;
	rotateX.SetRotationX(rotation.x);
	rotateY.SetRotationY(rotation.y);
	rotateZ.SetRotationZ(rotation.z);
	rotationMatrix = rotateX * rotateY * rotateZ;

	translation.SetTranslation(0.0f, 0.0f, 0.0f);

	world = scaleMatrix * rotationMatrix * translation;

	return world;
}

Matrix Object::CalculateWVP(Matrix modelMatrix, Matrix ViewPerspectiveMatrix)
{
	return modelMatrix * ViewPerspectiveMatrix;
}

void Object::Draw(Camera* camera)
{
	
	Matrix matrix = WorldMatrix();
	//WorldMatrix(matrix);
	//matrix = CalculateWVP(matrix, camera->view * camera->perspectiveMatrix);
	matrix = CalculateWVP(matrix, camera->LookAt());
	GLfloat matrixLine[16];

	matrixLine[0] = matrix.m[0][0];
	matrixLine[1] = matrix.m[0][1];
	matrixLine[2] = matrix.m[0][2];
	matrixLine[3] = matrix.m[0][3];

	matrixLine[4] = matrix.m[1][0];
	matrixLine[5] = matrix.m[1][1];
	matrixLine[6] = matrix.m[1][2];
	matrixLine[7] = matrix.m[1][3];

	matrixLine[8] = matrix.m[2][0];
	matrixLine[9] = matrix.m[2][1];
	matrixLine[10] = matrix.m[2][2];
	matrixLine[11] = matrix.m[2][3];

	matrixLine[12] = matrix.m[3][0];
	matrixLine[13] = matrix.m[3][1];
	matrixLine[14] = matrix.m[3][2];
	matrixLine[15] = matrix.m[3][3];

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
	glUniformMatrix4fv(iMatrixLoc, 1, GL_TRUE, matrixLine);
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
	Vector3 deltaMove = -(pos - Vector3(0.0f, 0.0f, 0.0f)).Normalize() * deltaTime * SceneManager::getInstance()->camera->moveSpeed;

	pos += deltaMove;	
}
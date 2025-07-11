#include "stdafx.h"
#include "Object.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "MVPMatrix.h"


Object::Object(Model* model, Texture* texture, Shaders* shader, Vector3 pos, Vector3 rotation, Vector3 scale)
{
	this->model = model;
	this->texture = texture;
	this->shader = shader;
	
	this->pos = pos;
	this->rotation = rotation;
	this->scale = scale;
}

void Object::Draw()
{
	MVPMatrix matrix;
	matrix.Init(pos, rotation, scale);
	matrix.Calculate();
	matrix.MatrixToArray();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthMask(GL_TRUE);

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
	glUniformMatrix4fv(iMatrixLoc, 1, GL_TRUE, matrix.mvpLine);
	// ibo object
	{
		glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::Update()
{

}
#include "stdafx.h"
#include "Animation.h"
#include "Globals.h"
#include "SceneManager.h"
#include "../Utilities/utilities.h"

// to adapt to row order anim, swap numactions and numframes
Animation::Animation(std::shared_ptr<Model> model, 
					 std::shared_ptr<Texture> texture, 
					 std::shared_ptr<Shaders> shader,
					 int frameTime,
					 int currentAction
	)
	: Object(model, texture, shader), m_currentFrame(1), m_currentTime(0.0f), m_currentAction(0), m_frameTime(0.0f)
{
	//m_pTexture = texture;
	//m_numFrames = numFrames;
	//m_numActions = numActions;
	m_frameTime = frameTime;
	m_currentFrame = 0;
	m_currentAction = currentAction;

	m_position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_scale = Vector3((float)m_iWidth / Globals::screenWidth, (float)m_iHeight / Globals::screenHeight, 1);
}

void Animation::Draw()
{
	GLint iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = glGetUniformLocation(m_pShader->program, "u_numFrames");
	if (iTempShaderVariableGLID != -1) {
		glUniform1f(iTempShaderVariableGLID, m_numFrames);
	}
	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = glGetUniformLocation(m_pShader->program, "u_currentFrame");
	if (iTempShaderVariableGLID != -1) {
		glUniform1f(iTempShaderVariableGLID, m_currentFrame);
	}
	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = glGetUniformLocation(m_pShader->program, "u_numActions");
	if (iTempShaderVariableGLID != -1) {
		glUniform1f(iTempShaderVariableGLID, m_numActions);
	}
	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = glGetUniformLocation(m_pShader->program, "u_currentAction");
	if (iTempShaderVariableGLID != -1) {
		glUniform1f(iTempShaderVariableGLID, m_currentAction);
	}

	Matrix mvpMatrix = world *
		SceneManager::GetInstance()->camera->m_viewMatrix *
		SceneManager::GetInstance()->camera->m_perspectiveMatrix;
	// this line will be called by the current game state
	// to prevent subsequent obj draws from removing last draws
	//glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_pShader->program);

	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->iboId);

	// take location value from vertex/fragment shader. With Position we have location = 0
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	// texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pTexture->textureId);
	int iTextureLoc = glGetUniformLocation(m_pShader->program, "u_texture");
	glUniform1i(iTextureLoc, 0);
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}

	// mvp matrix
	int iMatrixLoc = glGetUniformLocation(m_pShader->program, "u_mvp");
	glUniformMatrix4fv(iMatrixLoc, 1, GL_FALSE, &mvpMatrix.m[0][0]);
	// ibo object
	{
		glDrawElements(GL_TRIANGLES, m_pModel->numberOfIndex, GL_UNSIGNED_INT, 0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Animation::Update(GLfloat deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_numFrames) {
			m_currentFrame = 0;
		}
		m_currentTime -= m_frameTime;
	}
}

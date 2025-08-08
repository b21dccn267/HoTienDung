#include "../Utilities/utilities.h"
#include "Animation.h"
#include "GameManager/SceneManager.h"
#include "Globals.h"

// to adapt to row order anim, swap numactions and numframes
Animation::Animation(std::shared_ptr<Model> model, 
					 std::shared_ptr<Texture> texture, 
					 std::shared_ptr<Shaders> shader,
					 int frameTime,
					 int currentAction
	)
	: Object(model, texture, shader), m_currentTime(0.0f), m_frameTime(0.0f)
{
	m_frameTime = frameTime;

	m_position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_scale = Vector3((float)m_iWidth / Globals::screenWidth, (float)m_iHeight / Globals::screenHeight, 1);
}

// converts number to sprite x y coord by:
// - numFrames to get y
// remainder to get x
void Animation::FrameNumberToCoord(int number)
{
	m_frameX = 0;
	m_frameY = 0;
	while (number >= m_numFramesPerRow) {
		number -= m_numFramesPerRow;
		m_frameY++;
	}
	m_frameY = m_numFramesPerColumn - m_frameY - 1;
	m_frameX = number;
}

void Animation::SetCustomFrames(std::vector<int> order)
{
	m_frameOrder = order;
	m_frameCount = 0;
	FrameNumberToCoord(m_frameOrder[m_frameCount]);
}

void Animation::SetCustomFrames(std::vector<int> order, bool isLooped)
{
	m_frameOrder = order;
	m_frameCount = 0;
	FrameNumberToCoord(m_frameOrder[m_frameCount]);
}

void Animation::CustomUpdate(GLfloat deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime >= m_frameTime) {
		m_frameCount++;
		if (m_frameCount >= m_frameOrder.size()) {
			m_frameCount = 0;
		}
		m_currentTime -= m_frameTime;
	}
	FrameNumberToCoord(m_frameOrder[m_frameCount]);
}

void Animation::CustomDraw()
{
	Matrix mvpMatrix = world *
		SceneManager::GetInstance()->camera->m_viewMatrix *
		SceneManager::GetInstance()->camera->m_perspectiveMatrix;
	// this line will be called by the current game state
	// to prevent subsequent obj draws from removing last draws
	//glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_pShader->program);

	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->iboId);

	GLint iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = glGetUniformLocation(m_pShader->program, "u_numFrames");
	if (iTempShaderVariableGLID != -1) {
		glUniform1f(iTempShaderVariableGLID, m_numFramesPerRow);
	}
	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = glGetUniformLocation(m_pShader->program, "u_frameX");
	if (iTempShaderVariableGLID != -1) {
		glUniform1f(iTempShaderVariableGLID, m_frameX);
	}
	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = glGetUniformLocation(m_pShader->program, "u_numActions");
	if (iTempShaderVariableGLID != -1) {
		glUniform1f(iTempShaderVariableGLID, m_numFramesPerColumn);
	}
	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = glGetUniformLocation(m_pShader->program, "u_frameY");
	if (iTempShaderVariableGLID != -1) {
		glUniform1f(iTempShaderVariableGLID, m_frameY);
	}
	// take location value from vertex/fragment shader. With Position we have location = 0
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	// texture
	glActiveTexture(GL_TEXTURE0 + m_pTexture->textureId);
	glBindTexture(GL_TEXTURE_2D, m_pTexture->textureId);
	int iTextureLoc = glGetUniformLocation(m_pShader->program, "u_texture");
	glUniform1i(iTextureLoc, 0 + m_pTexture->textureId);
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
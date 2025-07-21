#include "stdafx.h"
#include "GSPlay.h"
#include "SceneManager.h"
#include "TextRenderer.h"

void GSPlay::Init()
{
	m_gsPlayObjects.reserve(3);

	m_gsPlayObjects.emplace_back(SceneManager::GetInstance()->m_objects[1]);
	//m_gsPlayObjects[0]->texture = std::TextRenderer::GetInstance()->RenderText("something meaningful");
	m_gsPlayObjects[0]->Set2DPosition(Vector2(100.0f, 100.0f));
	m_gsPlayObjects[0]->SetSize(200.0f, 200.0f);

	printf("play init\n");
}

void GSPlay::Pause()
{
}

void GSPlay::Exit()
{
}

void GSPlay::Resume()
{
}

void GSPlay::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& x : m_gsPlayObjects) {
		x->Draw();
	}
}

void GSPlay::Update(float deltaTime)
{
}

void GSPlay::HandleKeyEvent(bool bIsPressed)
{
}

void GSPlay::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	x = 0;
}

void GSPlay::Cleanup()
{
}

GSPlay::~GSPlay()
{
}

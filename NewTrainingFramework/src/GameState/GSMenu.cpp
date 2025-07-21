#include "stdafx.h"
#include "GSMenu.h"
#include "SceneManager.h"

void GSMenu::Init()
{
	m_gsMenuObjects.reserve(3);

	m_gsMenuObjects.emplace_back(SceneManager::GetInstance()->m_objects[0]);
	m_gsMenuObjects.emplace_back(SceneManager::GetInstance()->m_objects[1]);
	m_gsMenuObjects.emplace_back(SceneManager::GetInstance()->m_objects[2]);



	m_gsMenuObjects[0]->Set2DPosition(Vector2(100.0f, 100.0f));
	m_gsMenuObjects[0]->SetSize(200.0f, 200.0f);
	m_gsMenuObjects[1]->Set2DPosition(Vector2(200.0f, 100.0f));
	m_gsMenuObjects[1]->SetSize(200.0f, 200.0f);
	m_gsMenuObjects[2]->Set2DPosition(Vector2(300.0f, 100.0f));
	m_gsMenuObjects[2]->SetSize(200.0f, 200.0f);
	printf("menu init\n");
}

void GSMenu::Pause()
{
}

void GSMenu::Exit()
{
}

void GSMenu::Resume()
{
	//SceneManager::getInstance()->Draw(m_object);
}

void GSMenu::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& x : m_gsMenuObjects) {
		x->Draw();
	}
}

void GSMenu::Update(float deltaTime)
{
}

void GSMenu::HandleKeyEvent(bool bIsPressed)
{
}

void GSMenu::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	x = 0;
}

void GSMenu::Cleanup()
{
}

GSMenu::~GSMenu()
{
}

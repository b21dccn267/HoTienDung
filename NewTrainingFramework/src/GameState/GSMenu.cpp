#include "stdafx.h"
#include "GSMenu.h"
#include "SceneManager.h"

void GSMenu::Init()
{
	m_gsMenuObjects.reserve(3);

	m_gsMenuObjects.emplace_back(SceneManager::GetInstance()->m_objects[0]);
	m_gsMenuObjects.emplace_back(SceneManager::GetInstance()->m_objects[1]);
	m_gsMenuObjects.emplace_back(SceneManager::GetInstance()->m_objects[2]);
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
}

void GSMenu::Update(float deltaTime)
{
}

void GSMenu::HandleKeyEvent(bool bIsPressed)
{
}

void GSMenu::HandleMouseEvent()
{
}

void GSMenu::Cleanup()
{
}

GSMenu::~GSMenu()
{
}

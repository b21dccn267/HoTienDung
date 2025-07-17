#include "stdafx.h"
#include "GSMenu.h"
#include "SceneManager.h"

void GSMenu::Init()
{
	m_object = SceneManager::getInstance()->m_objects[1];
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

void GSMenu::CreateState()
{
}

void GSMenu::Update()
{
}

void GSMenu::HandleKeyEvent()
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

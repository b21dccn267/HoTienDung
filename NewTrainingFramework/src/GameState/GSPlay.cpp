#include "stdafx.h"
#include "GSPlay.h"
#include "SceneManager.h"

void GSPlay::Init()
{
	m_object = SceneManager::GetInstance()->m_objects[3];
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
}

void GSPlay::Update(float deltaTime)
{
}

void GSPlay::HandleKeyEvent(bool bIsPressed)
{
}

void GSPlay::HandleMouseEvent()
{
}

void GSPlay::Cleanup()
{
}

GSPlay::~GSPlay()
{
}

#include "stdafx.h"
#include "GSPlay.h"
#include "SceneManager.h"

void GSPlay::Init()
{
	m_object = SceneManager::getInstance()->m_objects[3];
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

void GSPlay::CreateState()
{
}

void GSPlay::Update()
{
}

void GSPlay::HandleKeyEvent()
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

#include "stdafx.h"
#include "GSDebug.h"
#include "../GameManager/SceneManager.h"
#include "../GameManager/ResourceManager.h"
#include <memory>

void GSDebug::Init()
{
	m_gsDebugObjects.reserve(1);

	//m_gsDebugObjects.emplace_back(SceneManager::GetInstance()->m_objects[3]);
	//m_gsDebugObjects[0]->Set2DPosition(Vector2(100.0f, 100.0f));
	//m_gsDebugObjects[0]->SetSize(200.0f, 200.0f);

	printf("debug init\n");
}

void GSDebug::SwapObject(int id)
{
	//m_gsDebugObjects.clear();
	//m_gsDebugObjects.emplace_back(SceneManager::GetInstance()->m_objects[id]);
	//m_gsDebugObjects[0]->Set2DPosition(Vector2(100.0f, 100.0f));
	//m_gsDebugObjects[0]->SetSize(200.0f, 200.0f);
 
	//std::shared_ptr<Texture> texture = std::make_shared<Texture>("../Resources/2d/Textures/bg_play1.tga", 1);
	//m_gsDebugObjects[0]->texture = ResourceManager::GetInstance()->GetTexture(id);
}

void GSDebug::Pause()
{
}

void GSDebug::Exit()
{
}

void GSDebug::Resume()
{
}

void GSDebug::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& x : m_gsDebugObjects) {
		x->Draw();
	}
}

void GSDebug::Update(float deltaTime)
{
	for (auto& x : m_gsDebugObjects) {
		x->Update();
	}
}

void GSDebug::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		printf("gsDebugKeyEvent %c\n", key);
		switch (key) {
		case 0x31: // 1 key
			SwapObject(0);
			break;
		case 0x32:
			SwapObject(1);
			break;
		case 0x33:
			SwapObject(2);
			break;
		case 0x34:
			SwapObject(3);
			break;
		case 0x35:
			SwapObject(4);
			break;
		}
	}
}

void GSDebug::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
}

void GSDebug::Cleanup()
{
}

GSDebug::~GSDebug()
{
}

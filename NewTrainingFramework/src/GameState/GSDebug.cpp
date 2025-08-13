#include "GSDebug.h"
#include "GameManager/SceneManager.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/actors/AmogusGunner.h"
#include "Globals.h"
#include <memory>

void GSDebug::Init()
{
	m_gsDebugObjects.reserve(1);

	//m_gsDebugObjects.emplace_back(SceneManager::GetInstance()->m_objects[3]);
	//m_gsDebugObjects[0]->Set2DPosition(Vector2(100.0f, 100.0f));
	//m_gsDebugObjects[0]->SetSize(200.0f, 200.0f);
	m_test = std::make_shared<AmogusGunner>();
	m_test->m_anim->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	m_test->m_anim->SetSize(200, 200);
	m_test->TestAllSprites();
	//auto model = std::shared_ptr<Model>(ResourceManager::GetInstance()->GetModel(0));
	//auto texture = std::shared_ptr<Texture>(ResourceManager::GetInstance()->GetTexture(33));
	//auto shader = std::shared_ptr<Shaders>(ResourceManager::GetInstance()->GetShader(0));
	//auto object = std::make_shared<Object>(model, texture, shader);
	//object->Set2DPosition(Vector2(Globals::screenWidth / 2,Globals::screenHeight / 2));
	//object->SetSize(500, 500);

	//m_gsDebugObjects.emplace_back(object);
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
	//for (auto& x : m_gsDebugObjects) {
	//	x->Draw();
	//}
	m_test->Draw();
}

void GSDebug::Update(float deltaTime)
{
	//for (auto& x : m_gsDebugObjects) {
	//	x->Update();
	//}
	m_test->Update(deltaTime);
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

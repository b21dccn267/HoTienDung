#include "GameButton.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameObject/core/Model.h"
#include "GameObject/core/Object.h"
#include "GameObject/core/Shaders.h"
#include "GameObject/core/Texture.h"
#include "GameStateBase.h"
#include "GameStateMachine.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include <memory>
#include <Windows.h>


void GSIntro::Init()
{
	m_gsIntroObjects.reserve(1);
	//m_gsIntroObjects.emplace_back(SceneManager::GetInstance()->m_objects[4]);
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(0);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	auto introObject = std::make_shared<Object>(model, texture, shader);
	introObject->Set2DPosition(Vector2(0.0f, 0.0f));
	introObject->SetSize(600.0f, 600.0f);
	m_gsIntroObjects.emplace_back(introObject);

	//m_gsIntroObjects[0]->Set2DPosition(Vector2(0.0f, 0.0f));
	//m_gsIntroObjects[0]->SetSize(600.0f, 600.0f);
	printf("intro init\n");
}

void GSIntro::Pause()
{
}

void GSIntro::Exit()
{
}

// init menu state then push
void GSIntro::Resume()
{
	//printf("Sleeping\n");
	
}

void GSIntro::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& x : m_gsIntroObjects) {
		x->Draw();
	}
	//Resume();
}

void GSIntro::Update(float deltaTime)
{
	Sleep(1000);
	printf("Slept for 1s, loading menu...\n");
	GameStateMachine::GetInstance()->PushState(StateType::STATE_MENU);
	for (auto& x : m_gsIntroObjects) {
		x->Update();
	}
}

void GSIntro::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	printf("gsIntroKeyEvent\n");
}

void GSIntro::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	printf("gsIntroMouseEvent\n");
}

void GSIntro::Cleanup()
{
}

GSIntro::~GSIntro()
{
}

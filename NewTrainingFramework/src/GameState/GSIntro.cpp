#include "stdafx.h"
#include "GSIntro.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "Object.h"
#include "GameStateMachine.h"
#include "GameStateBase.h"
#include "GSMenu.h"
#include "SceneManager.h"
#include <memory>
#include <Windows.h>
#include "GameButton.h"

void GSIntro::Init()
{
	m_gsIntroObjects.reserve(3);
	//m_gsIntroObjects.resize(3);

	m_gsIntroObjects.emplace_back(SceneManager::GetInstance()->m_objects[0]);
	m_gsIntroObjects[0]->Set2DPosition(Vector2(100.0f, 100.0f));
	m_gsIntroObjects[0]->SetSize(200.0f, 200.0f);

	//m_gsIntroObjects[1] = SceneManager::GetInstance()->m_objects[1];
	//m_gsIntroObjects[1]->Set2DPosition(Vector2(150.0f, 150.0f));
	//m_gsIntroObjects[1]->SetSize(200.0f, 200.0f);

	//m_gsIntroObjects = SceneManager::GetInstance()->m_objects[0];
	//std::shared_ptr<GameButton> button = std::make_shared<GameButton>(
	//	SceneManager::GetInstance()->m_objects[0]->model,
	//	SceneManager::GetInstance()->m_objects[0]->texture,
	//	SceneManager::GetInstance()->m_objects[0]->shader
	//);
	//button->Set2DPosition(Vector2(100.0f, 100.0f));
	//button->SetSize(150.0f, 150.0f);
	//button->SetOnClick([]() {
	//	GameStateMachine::GetInstance()->PerformStateChange(StateType::STATE_INTRO);
	//	});
	//button->Draw(); //fix


	//m_gsIntroObjects.emplace_back(SceneManager::GetInstance()->m_objects[1]); //bug
	//m_gsIntroObjects[1]->Set2DPosition(Vector2(100.0f, 100.0f));
	//m_gsIntroObjects[1]->SetSize(200.0f, 200.0f);
	/*m_gsIntroObjects->SetOnClick([]() {
		GameStateMachine::GetInstance()->PerformStateChange(StateType::STATE_INTRO);
		});*/
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
	//SceneManager::getInstance()->Draw(m_gsIntroObjects);
	printf("Sleeping\n");
	Sleep(2000);
	printf("Slept for 2s\n");
}

void GSIntro::Draw()
{
	for (auto& x : m_gsIntroObjects) {
		x->Draw();
	}
	//m_gsIntroObjects->Draw();
}

void GSIntro::Update(float deltaTime)
{
	for (auto& x : m_gsIntroObjects) {
		x->Update();
	}
	//m_gsIntroObjects->Update();
}

void GSIntro::HandleKeyEvent(bool bIsPressed)
{
	printf("gsIntroKeyPresed\n");
	switch (bIsPressed) {
	case 0x09 :
		printf("up pressed\n");
		break;
	}

	//switch
}

void GSIntro::HandleMouseEvent()
{
}

void GSIntro::Cleanup()
{
}

// state contains assets
// state should be able to control these assets
// game state vs sceneman
// state are modular, holds certain assets, is linked to other states and call them on the stack of gsm
// sceneman manages asset loading(constructing objects) as well as displaying, updating...
// 
// new form: 
// resman does asset loading and store them based on type
// sceneman bundles them into objects
// state pick these objects
//GameStateBase GSIntro::CreateState()
//{
//	//std::unique_ptr<Model> model = std::make_unique<Model>(new Model(modelFileName));
//	return GameStateBase();
//	//std::unique_ptr<Object> object = std::make_unique<Object>(new Object(model, texture, shader, pos, rotation, scale);
//}

GSIntro::~GSIntro()
{
}

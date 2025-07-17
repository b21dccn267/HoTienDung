#include "stdafx.h"
#include "GSIntro.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "Object.h"
#include "StateType.h"
#include "GameStateMachine.h"
#include "GameStateBase.h"
#include "GSMenu.h"
#include "SceneManager.h"
#include <memory>
#include <Windows.h>

void GSIntro::Init()
{
	//m_object = std::make_shared<Object> (SceneManager::getInstance()->m_objects[0]);
	m_object = SceneManager::getInstance()->m_objects[0];
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
	//SceneManager::getInstance()->Draw(m_object);
	//printf("Sleeping\n");
	//Sleep(2000);
	//printf("Slept for 2s\n");
	//
	//menu->Init();

}


void GSIntro::CreateState()
{
}

void GSIntro::Update()
{
	//SceneManager::getInstance()->Update();
	//m_object->Update();
}

void GSIntro::HandleKeyEvent()
{
	printf("gsIntroKeyPresed\n");

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

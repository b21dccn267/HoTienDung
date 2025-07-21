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
#include "ResourceManager.h"
#include <memory>
#include <Windows.h>
#include "GameButton.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


void GSIntro::Init()
{
	m_gsIntroObjects.reserve(3);
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(3);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> gameButton = std::make_shared<GameButton>(model, texture, shader);
	gameButton->Set2DPosition(Vector2(100.0f, 100.0f));
	gameButton->SetSize(200.0f, 200.0f);
	gameButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PerformStateChange(StateType::STATE_MENU);
		});

	m_gsIntroGameButtons.push_back(gameButton);
	 
	//m_gsIntroObjects.emplace_back(SceneManager::GetInstance()->m_objects[0]);

	//m_gsIntroObjects[0]->Set2DPosition(Vector2(100.0f, 100.0f));
	//m_gsIntroObjects[0]->SetSize(200.0f, 200.0f);

	//TTF_Font* font = TTF_OpenFont("../Resources/Fonts/Roboto-VariableFont_wdth,wght.ttf", 24);
	//if (!font) {
	//	return;
	//}

	//const char* message = "something meaningful";
	//SDL_Color white = { 255, 255, 255, 255 };

	//SDL_Surface* surface = TTF_RenderUTF8_Blended(font, message, white);
	//if (!surface) {
	//	return;
	//}
	//SDL_Renderer* renderer = nullptr;
	//SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
	//SDL_FreeSurface(surface);
	//if (!textTexture) {
	//	return;
	//}

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
	printf("Sleeping\n");
	Sleep(2000);
	printf("Slept for 2s\n");
}

void GSIntro::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& x : m_gsIntroObjects) {
		x->Draw();
	}
	for (auto& x : m_gsIntroGameButtons) {
		x->Draw();
	}
}

void GSIntro::Update(float deltaTime)
{
	for (auto& x : m_gsIntroObjects) {
		x->Update();
	}
	for (auto& x : m_gsIntroGameButtons) {
		x->Update();
	}
}

void GSIntro::HandleKeyEvent(bool bIsPressed)
{
	printf("gsIntroKeyPresed\n");
	switch (bIsPressed) {
	case 0x09 :
		printf("up pressed\n");
		break;
	}
}

void GSIntro::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	m_gsIntroGameButtons[0]->HandleTouchEvents(x, y, bIsPressed);
	//for (auto& x : m_gsIntroObjects) {}
	//for (auto& x : m_gsIntroGameButtons) {
	//	x->HandleTouchEvents(x, y, bIsPressed);
	//}
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

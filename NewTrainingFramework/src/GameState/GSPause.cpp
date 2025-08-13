#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameObject/core/TextRenderer.h"
#include "GameObject/core/Texture.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSPause.h"

void GSPause::Init()
{
	m_gsPauseObjects.reserve(8);
	m_gsPauseButtons.reserve(8);

	// background
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(32);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	auto overlay = std::make_shared<Object>(model, texture, shader);
	overlay->Set2DPosition(Vector2(Globals::screenWidth /2, Globals::screenHeight /2));
	overlay->SetSize(Globals::screenWidth, Globals::screenHeight);

	// continue button
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(31);  
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnResume = std::make_shared<GameButton>(model, texture, shader);
	btnResume->Set2DPosition(Vector2(Globals::screenWidth / 2 + 50, Globals::screenHeight / 2 + 45));
	btnResume->SetSize(65.0f, 65.0f);
	btnResume->SetOnClick(OnResumeButtonClick);

	// Home button
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(31);
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnMainMenu = std::make_shared<GameButton>(model, texture, shader);
	btnMainMenu->Set2DPosition(Vector2(Globals::screenWidth / 2 - 42, Globals::screenHeight / 2 + 43));
	btnMainMenu->SetSize(60.0f, 60.0f);
	btnMainMenu->SetOnClick(OnMainMenuButtonClick);

	m_gsPauseObjects.emplace_back(overlay);

	m_gsPauseButtons.emplace_back(btnResume);
	m_gsPauseButtons.emplace_back(btnMainMenu);

	printf("pause init\n");
}

void GSPause::Pause()
{
}

void GSPause::Exit()
{
}

void GSPause::Resume()
{
}

void GSPause::Draw()
{
	// Don't clear color buffer to show the game behind
	for (auto& obj : m_gsPauseObjects) {
		obj->Draw();
	}
	for (auto& btn : m_gsPauseButtons) {
		btn->Draw();
	}
}

void GSPause::Update(float deltaTime)
{
	for (auto& obj : m_gsPauseObjects) {
		obj->Update(deltaTime);
	}
	for (auto& btn : m_gsPauseButtons) {
		btn->Update(deltaTime);
	}
}

void GSPause::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		switch (key) {
		case 27: // ESC key
			GameStateMachine::GetInstance()->PopState(); // Resume game
			break;
		}
	}
}

void GSPause::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	for (auto& btn : m_gsPauseButtons) {
		if (btn->HandleTouchEvents(x, y, bIsPressed)) {
			break; // Stop processing if a button handled the event
		}
	}
}

void GSPause::Cleanup()
{
	m_gsPauseObjects.clear();
	m_gsPauseButtons.clear();
}

void GSPause::OnResumeButtonClick()
{
	// Pop the pause state to return to game
	GameStateMachine::GetInstance()->PopState();
}

void GSPause::OnMainMenuButtonClick()
{
	// Pop pause state and push menu state
	GameStateMachine::GetInstance()->PopState(); // Remove pause
}

GSPause::~GSPause()
{
}
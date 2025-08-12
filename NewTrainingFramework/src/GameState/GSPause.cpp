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
	texture = ResourceManager::GetInstance()->GetTexture(13);
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnMainMenu = std::make_shared<GameButton>(model, texture, shader);
	btnMainMenu->Set2DPosition(Vector2(Globals::screenWidth / 2 - 70, Globals::screenHeight / 2 + 10));
	btnMainMenu->SetSize(40.0f, 40.0f);
	btnMainMenu->SetOnClick(OnMainMenuButtonClick);

	//// soundup button
	//model = ResourceManager::GetInstance()->GetModel(0);
	//normalTexture = ResourceManager::GetInstance()->GetTexture(26);
	//pressedTexture = ResourceManager::GetInstance()->GetTexture(27);
	//shader = ResourceManager::GetInstance()->GetShader(0);
	//auto btnSoundUp = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	//btnSoundUp->Set2DPosition(Vector2(Globals::screenWidth / 2 - 70, Globals::screenHeight / 2 + 70));
	//btnSoundUp->SetSize(40.0f, 40.0f);

	//// soundfxup button
	//model = ResourceManager::GetInstance()->GetModel(0);
	//normalTexture = ResourceManager::GetInstance()->GetTexture(26);
	//pressedTexture = ResourceManager::GetInstance()->GetTexture(27);
	//shader = ResourceManager::GetInstance()->GetShader(0);
	//auto btnSoundFXUp = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	//btnSoundFXUp->Set2DPosition(Vector2(Globals::screenWidth / 2 - 70, Globals::screenHeight / 2 + 130));
	//btnSoundFXUp->SetSize(40.0f, 40.0f);

	//// sounddown button
	//model = ResourceManager::GetInstance()->GetModel(0);
	//normalTexture = ResourceManager::GetInstance()->GetTexture(29);
	//pressedTexture = ResourceManager::GetInstance()->GetTexture(28);
	//shader = ResourceManager::GetInstance()->GetShader(0);
	//auto btnSoundDown = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	//btnSoundDown->Set2DPosition(Vector2(Globals::screenWidth / 2 + 85, Globals::screenHeight / 2 + 70));
	//btnSoundDown->SetSize(40.0f, 40.0f);

	//// soundfxdown button
	//model = ResourceManager::GetInstance()->GetModel(0);
	//normalTexture = ResourceManager::GetInstance()->GetTexture(29);
	//pressedTexture = ResourceManager::GetInstance()->GetTexture(28);
	//shader = ResourceManager::GetInstance()->GetShader(0);
	//auto btnSoundFXDown = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	//btnSoundFXDown->Set2DPosition(Vector2(Globals::screenWidth / 2 + 85, Globals::screenHeight / 2 + 130));
	//btnSoundFXDown->SetSize(40.0f, 40.0f);


	m_gsPauseObjects.emplace_back(overlay);

	m_gsPauseButtons.emplace_back(btnResume);
	m_gsPauseButtons.emplace_back(btnMainMenu);
	
	//m_gsPauseButtons.emplace_back(btnSoundUp);
	//m_gsPauseButtons.emplace_back(btnSoundFXUp);
	//m_gsPauseButtons.emplace_back(btnSoundDown);
	//m_gsPauseButtons.emplace_back(btnSoundFXDown);

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
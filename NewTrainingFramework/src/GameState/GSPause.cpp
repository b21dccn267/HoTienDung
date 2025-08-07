#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameObject/core/TextRenderer.h"
#include "GameObject/core/Texture.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSPause.h"

void GSPause::Init()
{
	m_gsPauseObjects.reserve(2);
	m_gsPauseButtons.reserve(2);

	// background
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(0);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	auto overlay = std::make_shared<Object>(model, texture, shader);
	overlay->Set2DPosition(Vector2(Globals::screenWidth /2, Globals::screenHeight /2));
	overlay->SetSize(Globals::screenWidth, Globals::screenHeight);

	// Pause menu background
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(18);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<Object> pauseBg = std::make_shared<Object>(model, texture, shader);
	pauseBg->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2 + 20));
	pauseBg->SetSize(321.0f, 454.0f);


	// continue button
	model = ResourceManager::GetInstance()->GetModel(0);
	auto normalTexture = ResourceManager::GetInstance()->GetTexture(15);   // Texture cho continue button nổi
	auto pressedTexture = ResourceManager::GetInstance()->GetTexture(16);  // Texture cho continue button chìm 
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnResume = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	btnResume->Set2DPosition(Vector2(Globals::screenWidth / 2 - 80, Globals::screenHeight / 2 - 50));
	btnResume->SetSize(60.0f, 60.0f);
	btnResume->SetOnClick(OnResumeButtonClick);

	// Home button
	model = ResourceManager::GetInstance()->GetModel(0);
	normalTexture = ResourceManager::GetInstance()->GetTexture(13);
	pressedTexture = ResourceManager::GetInstance()->GetTexture(14);
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnMainMenu = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	btnMainMenu->Set2DPosition(Vector2(Globals::screenWidth / 2 - 80, Globals::screenHeight / 2 + 20));
	btnMainMenu->SetSize(60.0f, 60.0f);
	btnMainMenu->SetOnClick(OnMainMenuButtonClick);

	////sound button
	//model = ResourceManager::GetInstance()->GetModel(0);
	//texture = ResourceManager::GetInstance()->GetTexture(17);
	//shader = ResourceManager::GetInstance()->GetShader(0);
	//auto btnSound = std::make_shared<GameButton>(model, texture, shader);
	//btnSound->Set2DPosition(Vector2(Globals::screenWidth / 2 - 80, Globals::screenHeight / 2 + 90));
	//btnSound->SetSize(60.0f, 60.0f);

	// text - paused
	auto textPaused = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("Game Paused")),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textPaused->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 8));
	textPaused->SetSize(600.0f, 100.0f);

	// text - continue
	auto textContinue = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("Continue")),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textContinue->Set2DPosition(Vector2(Globals::screenWidth / 2 + 20, Globals::screenHeight / 2 - 50));
	textContinue->SetSize(100.0f, 20.0f);

	// text - home
	auto textHome = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("Home")),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textHome->Set2DPosition(Vector2(Globals::screenWidth / 2 + 20, Globals::screenHeight / 2 + 20));
	textHome->SetSize(100.0f, 20.0f);

	//// text - sound 
	//auto textSound = std::make_shared<Object>(
	//	ResourceManager::GetInstance()->GetModel(0),
	//	std::make_shared<Texture>(TextRenderer::RenderText("Sound ON/OFF")),
	//	ResourceManager::GetInstance()->GetShader(0)
	//);
	//textSound->Set2DPosition(Vector2(Globals::screenWidth / 2 + 20, Globals::screenHeight / 2 + 90));
	//textSound->SetSize(100.0f, 20.0f);

	m_gsPauseObjects.emplace_back(overlay);
	m_gsPauseObjects.emplace_back(pauseBg);

	m_gsPauseObjects.emplace_back(textPaused);
	m_gsPauseObjects.emplace_back(textContinue);
	m_gsPauseObjects.emplace_back(textHome);
	//m_gsPauseObjects.emplace_back(textSound);

	m_gsPauseButtons.emplace_back(btnResume);
	m_gsPauseButtons.emplace_back(btnMainMenu);
	//m_gsPauseButtons.emplace_back(btnSound);

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
	GameStateMachine::GetInstance()->PopState(); // Remove play
	//GameStateMachine::GetInstance()->PushState(StateType::STATE_MENU);
}

GSPause::~GSPause()
{
}
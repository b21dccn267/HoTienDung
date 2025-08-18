#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameObject/core/TextRenderer.h"
#include "GameObject/core/Texture.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSGameOver.h"

std::string GSGameOver::s_pendingCustomText = "";

void GSGameOver::Init()
{
	m_gameOverObjects.reserve(8);
	m_gameOverButtons.reserve(8);

	// Background
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(33); // Same background as pause
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	auto overlay = std::make_shared<Object>(model, texture, shader);
	overlay->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	overlay->SetSize(Globals::screenWidth, Globals::screenHeight);

	// Title text - GAME OVER
	auto textGameOver = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("GAME OVER", "../Resources/Fonts/ChangaOne-Regular.ttf", 58)),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textGameOver->Set2DPosition(Vector2(Globals::screenWidth / 2, 100.0f));
	textGameOver->SetSize(500.0f, 120.0f);

	// Custom text (if provided)
	if (!s_pendingCustomText.empty()) {
		m_customText = s_pendingCustomText;
		s_pendingCustomText = ""; // Clear after use
	}
	std::shared_ptr<Object> textCustom = nullptr;
	if (!m_customText.empty()) {
		textCustom = std::make_shared<Object>(
			ResourceManager::GetInstance()->GetModel(0),
			std::make_shared<Texture>(TextRenderer::RenderText(m_customText.c_str(), "../Resources/Fonts/ChangaOne-Regular.ttf", 36)),
			ResourceManager::GetInstance()->GetShader(0)
		);
		textCustom->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2 - 50));
		textCustom->SetSize(400.0f, 80.0f);
	}

	// Restart button (left button)
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(22); // Restart button texture - thay đổi ID theo texture của bạn
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnRestart = std::make_shared<GameButton>(model, texture, shader);
	btnRestart->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, Globals::screenHeight / 2 + 45));
	btnRestart->SetSize(65.0f, 65.0f);
	btnRestart->SetOnClick(OnRestartButtonClick);

	// Home button (right button)
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(36); // Home button texture
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnMainMenu = std::make_shared<GameButton>(model, texture, shader);
	btnMainMenu->Set2DPosition(Vector2(Globals::screenWidth / 2 + 50, Globals::screenHeight / 2 + 45));
	btnMainMenu->SetSize(66.0f, 68.0f);
	btnMainMenu->SetOnClick(OnMainMenuButtonClick);

	m_gameOverObjects.emplace_back(overlay);
	m_gameOverObjects.emplace_back(textGameOver);
	if (textCustom) {
		m_gameOverObjects.emplace_back(textCustom);
	}
	m_gameOverButtons.emplace_back(btnRestart);
	m_gameOverButtons.emplace_back(btnMainMenu);

	printf("Game Over init\n");
}

void GSGameOver::Pause()
{
}

void GSGameOver::Exit()
{
}

void GSGameOver::Resume()
{
}

void GSGameOver::Draw()
{
	for (auto& obj : m_gameOverObjects) {
		obj->Draw();
	}
	for (auto& btn : m_gameOverButtons) {
		btn->Draw();
	}
}

void GSGameOver::Update(float deltaTime)
{
	for (auto& obj : m_gameOverObjects) {
		obj->Update(deltaTime);
	}
	for (auto& btn : m_gameOverButtons) {
		btn->Update(deltaTime);
	}
}

void GSGameOver::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		switch (key) {
		case 'r': // R key to restart
		case 'R':
			OnRestartButtonClick();
			break;
		case 27: // ESC key to main menu
			OnMainMenuButtonClick();
			break;
		}
	}
}

void GSGameOver::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	for (auto& btn : m_gameOverButtons) {
		if (btn->HandleTouchEvents(x, y, bIsPressed)) {
			break; // Stop processing if a button handled the event
		}
	}
}

void GSGameOver::Cleanup()
{
	m_gameOverObjects.clear();
	m_gameOverButtons.clear();
}

void GSGameOver::OnRestartButtonClick()
{
	// Pop game over state and restart the game
	GameStateMachine::GetInstance()->PopState();
	// Assuming you have a game state to push - adjust according to your game structure
	// GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
}

void GSGameOver::OnMainMenuButtonClick()
{
	// Pop game over state and go to main menu
	GameStateMachine::GetInstance()->PopState();
	// Pop any remaining game states to get to main menu
	// GameStateMachine::GetInstance()->PushState(StateType::STATE_MENU);
}

GSGameOver::~GSGameOver()
{
}
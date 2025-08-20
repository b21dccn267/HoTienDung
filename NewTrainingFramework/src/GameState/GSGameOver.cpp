#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameObject/core/TextRenderer.h"
#include "GameObject/core/Texture.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSGameOver.h"

std::string GSGameOver::s_pendingMainText = "";
std::string GSGameOver::s_pendingSubText = "";

void GSGameOver::Init()
{
	m_gameOverObjects.reserve(8);
	m_gameOverButtons.reserve(8);

	if (!s_pendingMainText.empty()) {
		m_mainText = s_pendingMainText;
		s_pendingMainText = ""; 
	}
	if (!s_pendingSubText.empty()) {
		m_subText = s_pendingSubText;
		s_pendingSubText = ""; 
	}

	// Background
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(33);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	auto overlay = std::make_shared<Object>(model, texture, shader);
	overlay->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	overlay->SetSize(Globals::screenWidth, Globals::screenHeight);

	// Main title text 
	auto textMain = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText(m_mainText.c_str(), "../Resources/Fonts/ChangaOne-Regular.ttf", 58)),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textMain->Set2DPosition(Vector2(Globals::screenWidth / 2, 100.0f));
	textMain->SetSize(500.0f, 120.0f);

	// Subtitle text 
	std::shared_ptr<Object> textSub = nullptr;
	if (!m_subText.empty()) {
		textSub = std::make_shared<Object>(
			ResourceManager::GetInstance()->GetModel(0),
			std::make_shared<Texture>(TextRenderer::RenderText(m_subText.c_str(), "../Resources/Fonts/ChangaOne-Regular.ttf", 36)),
			ResourceManager::GetInstance()->GetShader(0)
		);
		textSub->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2 - 50));
		textSub->SetSize(400.0f, 80.0f);
	}

	// Restart button (left button)
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(44);
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnRestart = std::make_shared<GameButton>(model, texture, shader);
	btnRestart->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, Globals::screenHeight / 2 + 45));
	btnRestart->SetSize(65.0f, 65.0f);
	btnRestart->SetOnClick(OnRestartButtonClick);

	// Home button (right button)
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(36);
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnMainMenu = std::make_shared<GameButton>(model, texture, shader);
	btnMainMenu->Set2DPosition(Vector2(Globals::screenWidth / 2 + 50, Globals::screenHeight / 2 + 45));
	btnMainMenu->SetSize(66.0f, 68.0f);
	btnMainMenu->SetOnClick(OnMainMenuButtonClick);

	m_gameOverObjects.emplace_back(overlay);
	m_gameOverObjects.emplace_back(textMain);
	if (textSub) {
		m_gameOverObjects.emplace_back(textSub);
	}
	m_gameOverButtons.emplace_back(btnRestart);
	m_gameOverButtons.emplace_back(btnMainMenu);

	printf("Game Over init with text: %s\n", m_mainText.c_str());
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
			break; 
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
	GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
}

void GSGameOver::OnMainMenuButtonClick()
{
	GameStateMachine::GetInstance()->PopState();
	GameStateMachine::GetInstance()->PushState(StateType::STATE_MENU);
}

void GSGameOver::SetPendingText(const std::string& mainText, const std::string& subText)
{
	s_pendingMainText = mainText;
	s_pendingSubText = subText;
}

GSGameOver::~GSGameOver()
{
}
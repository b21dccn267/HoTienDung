#include "GameButton.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameObject/core/Object.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), m_isSoundOn(true)
{
}

void GSMenu::Init()
{
	m_gsMenuObjects.reserve(5);  
	m_gsMenuGameButtons.reserve(5);

	// menu background - sound on/off
	auto model = ResourceManager::GetInstance()->GetModel(0);
	// Bắt đầu với sound on background
	auto texture = ResourceManager::GetInstance()->GetTexture(0);  // Sound on background texture ID
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	m_soundBg = std::make_shared<Object>(model, texture, shader);
	m_soundBg->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	m_soundBg->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_gsMenuObjects.emplace_back(m_soundBg);

	// play button
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(31); 
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> menuButton = std::make_shared<GameButton>(model, texture, shader);
	menuButton->Set2DPosition(Vector2(Globals::screenWidth / 2 , 320.0f));
	menuButton->SetSize(150.0f, 85.0f);
	menuButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
		});
	m_gsMenuGameButtons.emplace_back(menuButton);

	// settings button
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(31);  
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> settingsButton = std::make_shared<GameButton>(model, texture, shader);
	settingsButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 420, 630.0f));
	settingsButton->SetSize(60.0f, 80.0f);
	settingsButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_SETTINGS);
		});
	m_gsMenuGameButtons.emplace_back(settingsButton);

	// invisible sound toggle button 
	model = ResourceManager::GetInstance()->GetModel(0);
	auto emptyTexture = ResourceManager::GetInstance()->GetTexture(31);  // Empty/transparent texture
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> soundToggleButton = std::make_shared<GameButton>(model, emptyTexture, shader);
	soundToggleButton->Set2DPosition(Vector2(60.0f, 632.0f)); 
	soundToggleButton->SetSize(60.0f, 75.0f); 

	soundToggleButton->SetOnClick([this]() {
		ToggleSound();
		});
	m_gsMenuGameButtons.emplace_back(soundToggleButton);

	printf("menu init\n");
}

void GSMenu::ToggleSound()
{
	m_isSoundOn = !m_isSoundOn;

	// Thay đổi texture của background dựa trên trạng thái sound
	if (m_isSoundOn) {
		auto soundOnTexture = ResourceManager::GetInstance()->GetTexture(0);
		m_soundBg->m_pTexture = soundOnTexture;
	}
	else {
		auto soundOffTexture = ResourceManager::GetInstance()->GetTexture(30);
		m_soundBg->m_pTexture = soundOffTexture;
	}

	printf("Sound toggled: %s\n", m_isSoundOn ? "ON" : "OFF");
}

void GSMenu::Pause()
{
}

void GSMenu::Exit()
{
}

void GSMenu::Resume()
{

}

void GSMenu::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& x : m_gsMenuObjects) {
		x->Draw();
	}
	for (auto& x : m_gsMenuGameButtons) {
		x->Draw();
	}
}

void GSMenu::Update(float deltaTime)
{
	for (auto& x : m_gsMenuObjects) {
		x->Update(deltaTime);
	}
	for (auto& x : m_gsMenuGameButtons) {
		x->Update(deltaTime);
	}
}

void GSMenu::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	printf("gsMenuKeyPresed: %c\n", key);
}

void GSMenu::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	for (auto& btn : m_gsMenuGameButtons) {
		btn->HandleTouchEvents(x, y, bIsPressed);
	}
}

void GSMenu::Cleanup()
{
}

GSMenu::~GSMenu()
{
}
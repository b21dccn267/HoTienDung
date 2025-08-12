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
	m_gsMenuObjects.reserve(5);  // Tăng lên để chứa sound background
	m_gsMenuGameButtons.reserve(5);

	//// background
	//auto model = ResourceManager::GetInstance()->GetModel(0);
	//auto texture = ResourceManager::GetInstance()->GetTexture(0);
	//auto shader = ResourceManager::GetInstance()->GetShader(0);
	//std::shared_ptr<Object> background = std::make_shared<Object>(model, texture, shader);
	//background->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	//background->SetSize(Globals::screenWidth, Globals::screenHeight);
	//m_gsMenuObjects.emplace_back(background);

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
	texture = ResourceManager::GetInstance()->GetTexture(31);   // Texture cho play button nổi
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> menuButton = std::make_shared<GameButton>(model, texture, shader);
	menuButton->Set2DPosition(Vector2(Globals::screenWidth / 2 , 320.0f));
	menuButton->SetSize(150.0f, 85.0f);
	menuButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
		});
	m_gsMenuGameButtons.emplace_back(menuButton);

	//// settings button
	//model = ResourceManager::GetInstance()->GetModel(0);
	//normalTexture = ResourceManager::GetInstance()->GetTexture(21);   // Texture cho settings button nổi
	//pressedTexture = ResourceManager::GetInstance()->GetTexture(23);  // Texture cho settings button chìm
	//shader = ResourceManager::GetInstance()->GetShader(0);
	//std::shared_ptr<GameButton> settingsButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	//settingsButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 320.0f));
	//settingsButton->SetSize(150.0f, 45.0f);
	//settingsButton->SetOnClick([]() {
	//	GameStateMachine::GetInstance()->PushState(StateType::STATE_SETTINGS);
	//	});
	//m_gsMenuGameButtons.emplace_back(settingsButton);

	//// quit button  
	//model = ResourceManager::GetInstance()->GetModel(0);
	//normalTexture = ResourceManager::GetInstance()->GetTexture(1);   // Texture cho close button nổi
	//pressedTexture = ResourceManager::GetInstance()->GetTexture(2);  // Texture cho close button chìm
	//shader = ResourceManager::GetInstance()->GetShader(0);
	//std::shared_ptr<GameButton> closeButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	//closeButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 386.0f));
	//closeButton->SetSize(150.0f, 45.0f);
	//closeButton->SetOnClick([]() {
	//	exit(0);
	//	});
	//m_gsMenuGameButtons.emplace_back(closeButton);

	// invisible sound toggle button - tạo button vô hình ở vị trí sound icon
	model = ResourceManager::GetInstance()->GetModel(0);
	// Tạo texture transparent hoặc sử dụng texture rỗng
	// Giả sử texture ID 999 là texture transparent/empty
	auto emptyTexture = ResourceManager::GetInstance()->GetTexture(31);  // Empty/transparent texture
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> soundToggleButton = std::make_shared<GameButton>(model, emptyTexture, emptyTexture, shader);

	// Đặt vị trí button ở góc trái (sound icon position)
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
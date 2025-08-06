#include "GameButton.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameObject/core/Object.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSMenu.h"


void GSMenu::Init()
{
	m_gsMenuObjects.reserve(4);
	m_gsMenuGameButtons.reserve(5);

// background
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(0);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<Object> background = std::make_shared<Object>(model, texture, shader);
	background->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_gsMenuObjects.emplace_back(background);

// menu background
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(19);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<Object> MenuBg = std::make_shared<Object>(model, texture, shader);
	MenuBg->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2 - 50));
	MenuBg->SetSize(321.0f, 404.0f);
	m_gsMenuObjects.emplace_back(MenuBg);

// play button
	model = ResourceManager::GetInstance()->GetModel(0);
	auto normalTexture = ResourceManager::GetInstance()->GetTexture(22);   // Texture cho play button nổi
	auto pressedTexture = ResourceManager::GetInstance()->GetTexture(21);  // Texture cho play button chìm 
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> menuButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	menuButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 255.0f));
	menuButton->SetSize(150.0f, 45.0f);
	menuButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
		});
	m_gsMenuGameButtons.emplace_back(menuButton);

// settings button
    model = ResourceManager::GetInstance()->GetModel(0);
    normalTexture = ResourceManager::GetInstance()->GetTexture(25);   // Texture cho settings button nổi
    pressedTexture = ResourceManager::GetInstance()->GetTexture(26);  // Texture cho settings button chìm
    shader = ResourceManager::GetInstance()->GetShader(0);
    std::shared_ptr<GameButton> settingsButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
    settingsButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 320.0f));
    settingsButton->SetSize(150.0f, 45.0f);
    settingsButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_SETTINGS);
		});
    m_gsMenuGameButtons.emplace_back(settingsButton);

// quit button  
	model = ResourceManager::GetInstance()->GetModel(0);
	normalTexture = ResourceManager::GetInstance()->GetTexture(23);   // Texture cho close button nổi
	pressedTexture = ResourceManager::GetInstance()->GetTexture(24);  // Texture cho close button chìm
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> closeButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	closeButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 386.0f));
	closeButton->SetSize(150.0f, 45.0f);
	closeButton->SetOnClick([]() {
		exit(0);
		});
	m_gsMenuGameButtons.emplace_back(closeButton);



	//printf("menu init\n");
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
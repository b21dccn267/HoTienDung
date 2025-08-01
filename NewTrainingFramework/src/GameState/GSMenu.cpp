
#include "GSMenu.h"
#include "../GameObject/core/Object.h"
#include "../GameManager/SceneManager.h"
#include "../GameManager/ResourceManager.h"
#include "../Globals.h"
#include "GameStateMachine.h"
#include "GameButton.h"

void GSMenu::Init()
{
	m_gsMenuObjects.reserve(3);
	m_gsMenuGameButtons.reserve(5);
	
	// background
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(0);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<Object> background = std::make_shared<Object>(model, texture, shader);
	background->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_gsMenuObjects.emplace_back(background);

	// play button
	 model = ResourceManager::GetInstance()->GetModel(0);
	 texture = ResourceManager::GetInstance()->GetTexture(15);
	 shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> menuButton = std::make_shared<GameButton>(model, texture, shader);
	menuButton->Set2DPosition(Vector2(Globals::screenWidth/2, 500.0f));
	menuButton->SetSize(100.0f, 100.0f);
	menuButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
		});
	m_gsMenuGameButtons.emplace_back(menuButton);

	// close button
	 model = ResourceManager::GetInstance()->GetModel(0);
	 texture = ResourceManager::GetInstance()->GetTexture(13);
	 shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> closeButton = std::make_shared<GameButton>(model, texture, shader);
	closeButton->Set2DPosition(Vector2(250.0f, 500.0f));
	closeButton->SetSize(100.0f, 100.0f);
	closeButton->SetOnClick([]() {
		exit(0);
		});
	m_gsMenuGameButtons.emplace_back(closeButton);
	
	// settings button
	 model = ResourceManager::GetInstance()->GetModel(0);
	 texture = ResourceManager::GetInstance()->GetTexture(14);
	 shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> settingsButton = std::make_shared<GameButton>(model, texture, shader);
	settingsButton->Set2DPosition(Vector2(700.0f, 500.0f));
	settingsButton->SetSize(100.0f, 100.0f);
	settingsButton->SetOnClick([]() {
		printf("oke");
		});
	m_gsMenuGameButtons.emplace_back(settingsButton);

	printf("menu init\n");
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
	//if (bIsPressed) {
	//	switch (key) {
	//	case 0x31: // 1 pressed
	//		printf("1 pressed\n");
	//		break;
	//	}
	//}
}

void GSMenu::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	
	for (auto& btn : m_gsMenuGameButtons) {
		btn->HandleTouchEvents(x, y, bIsPressed);
	}
	//m_gsMenuGameButtons[0]->HandleTouchEvents(x, y, bIsPressed);
	//m_gsMenuGameButtons[1]->HandleTouchEvents(x, y, bIsPressed);
	//m_gsMenuGameButtons[2]->HandleTouchEvents(x, y, bIsPressed);
}

void GSMenu::Cleanup()
{
}

GSMenu::~GSMenu()
{
}

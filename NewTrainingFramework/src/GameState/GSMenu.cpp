#include "stdafx.h"
#include "GSMenu.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameStateMachine.h"

void GSMenu::Init()
{
	m_gsMenuObjects.reserve(3);
	m_gsMenuGameButtons.reserve(3);

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(3);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> gameButton = std::make_shared<GameButton>(model, texture, shader);
	gameButton->Set2DPosition(Vector2(100.0f, 100.0f));
	gameButton->SetSize(200.0f, 200.0f);
	gameButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PerformStateChange(StateType::STATE_PLAY);
		});

	m_gsMenuGameButtons.push_back(gameButton);

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
		x->Update();
	}
	for (auto& x : m_gsMenuGameButtons) {
		x->Update();
	}
}

void GSMenu::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	printf("gsMenuKeyPresed: %c\n", key);
	if (bIsPressed) {
		switch (key) {
		case 0x31: // 1 pressed
			printf("1 pressed\n");
			break;
		}
	}

}

void GSMenu::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	printf("gsMenuMouseEvent\n");
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

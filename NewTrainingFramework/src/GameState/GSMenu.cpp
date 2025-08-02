#include "GSMenu.h"
#include "../GameObject/core/Object.h"
#include "../GameManager/SceneManager.h"
#include "../GameManager/ResourceManager.h"
#include "../Globals.h"
#include "GameStateMachine.h"
#include "GameButton.h"

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
	texture = ResourceManager::GetInstance()->GetTexture(20);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<Object> MenuBg = std::make_shared<Object>(model, texture, shader);
	MenuBg->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2 - 50));
	MenuBg->SetSize(321.0f, 404.0f);
	m_gsMenuObjects.emplace_back(MenuBg);

	// play button
	auto CreateEmptyTexture = []() {
		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, 1, 1, 32, SDL_PIXELFORMAT_RGBA8888);
		SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
		return std::make_shared<Texture>(surface);
		};

	model = ResourceManager::GetInstance()->GetModel(0);
	auto emptyTexture = CreateEmptyTexture();
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> menuButton = std::make_shared<GameButton>(model, emptyTexture, shader);
	menuButton->Set2DPosition(Vector2(Globals::screenWidth/2 + 5, 255.0f));
	menuButton->SetSize(150.0f, 45.0f);
	menuButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
		});
	m_gsMenuGameButtons.emplace_back(menuButton);

	// close button
	model = ResourceManager::GetInstance()->GetModel(0);
	emptyTexture = CreateEmptyTexture();
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> closeButton = std::make_shared<GameButton>(model, emptyTexture, shader);
	closeButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 386.0f));
	closeButton->SetSize(150.0f, 45.0f);
	closeButton->SetOnClick([]() {
		exit(0);
		});
	m_gsMenuGameButtons.emplace_back(closeButton);
	
	// settings button
	model = ResourceManager::GetInstance()->GetModel(0);
	emptyTexture = CreateEmptyTexture();
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> settingsButton = std::make_shared<GameButton>(model, emptyTexture, shader);
	settingsButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 320.0f));
	settingsButton->SetSize(150.0f, 45.0f);
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

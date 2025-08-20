#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameObject/core/TextRenderer.h"
#include "GameManager/SoundManager.h"
#include "GameObject/core/Texture.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSPause.h"

void GSPause::Init()
{
	m_gsPauseObjects.reserve(8);
	m_gsPauseButtons.reserve(8);

	SoundManager::GetInstance()->LoadMusic("menu_music", "../Resources/Sfx/menu-music.wav");
	SoundManager::GetInstance()->LoadSfx("button_click_new", "../Resources/Sfx/click-sound.wav");

	// background
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(33);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	auto overlay = std::make_shared<Object>(model, texture, shader);
	overlay->Set2DPosition(Vector2(Globals::screenWidth /2, Globals::screenHeight /2));
	overlay->SetSize(Globals::screenWidth, Globals::screenHeight);

	// Title text - Settings
	auto textPause = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("PAUSED", "../Resources/Fonts/ChangaOne-Regular.ttf", 58)),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textPause->Set2DPosition(Vector2(Globals::screenWidth / 2, 100.0f));
	textPause->SetSize(400.0f, 120.0f);


	// continue button
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(22);  
	shader = ResourceManager::GetInstance()->GetShader(0); 
	auto btnResume = std::make_shared<GameButton>(model, texture, shader);
	btnResume->Set2DPosition(Vector2(Globals::screenWidth / 2 + 50, Globals::screenHeight / 2 + 45));
	btnResume->SetSize(65.0f, 65.0f);
	btnResume->SetOnClick([this]() {

		if (SoundManager::GetInstance()->IsSoundEnabled()) {
			SoundManager::GetInstance()->PlaySfx("button_click_new");
		}
		GameStateMachine::GetInstance()->PopState();
		});

	// Home button
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(36);
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnMainMenu = std::make_shared<GameButton>(model, texture, shader);
	btnMainMenu->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, Globals::screenHeight / 2 + 45));
	btnMainMenu->SetSize(66.0f, 68.0f);
	btnMainMenu->SetOnClick([this]() {

		if (SoundManager::GetInstance()->IsSoundEnabled()) {
			SoundManager::GetInstance()->PlaySfx("button_click_new");
		}
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		});

	m_gsPauseObjects.emplace_back(overlay);
	m_gsPauseObjects.emplace_back(textPause);
	m_gsPauseButtons.emplace_back(btnResume);
	m_gsPauseButtons.emplace_back(btnMainMenu);

	SoundManager::GetInstance()->PlayMusicIfEnabled("menu_music", -1);

	printf("Pause init\n");
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
		case 27: 
			GameStateMachine::GetInstance()->PopState(); // Resume game
			break;
		}
	}
}

void GSPause::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	for (auto& btn : m_gsPauseButtons) {
		if (btn->HandleTouchEvents(x, y, bIsPressed)) {
			break; 
		}
	}
}

void GSPause::Cleanup()
{
	m_gsPauseObjects.clear();
	m_gsPauseButtons.clear();
}

GSPause::~GSPause()
{
}
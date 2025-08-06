#include "GameButton.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameObject/core/Object.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSSettings.h"

void GSSettings::Init()
{
	m_gsSettingsObjects.reserve(4);
	m_gsSettingsGameButtons.reserve(5);

	// background
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(0);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<Object> background = std::make_shared<Object>(model, texture, shader);
	background->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_gsSettingsObjects.emplace_back(background);

	// settings background
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(19); // Có thể thay bằng texture riêng cho settings
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<Object> settingsBg = std::make_shared<Object>(model, texture, shader);
	settingsBg->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2 - 50));
	settingsBg->SetSize(321.0f, 404.0f);
	m_gsSettingsObjects.emplace_back(settingsBg);

	// sound on/off button (ví dụ)
	model = ResourceManager::GetInstance()->GetModel(0);
	auto normalTexture = ResourceManager::GetInstance()->GetTexture(22); // Thay bằng texture sound button
	auto pressedTexture = ResourceManager::GetInstance()->GetTexture(21); // Thay bằng texture sound button pressed
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> soundButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	soundButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 200.0f));
	soundButton->SetSize(150.0f, 45.0f);
	soundButton->SetOnClick([]() {
		printf("Sound toggle clicked\n");
		// Thêm logic toggle sound ở đây
		});
	m_gsSettingsGameButtons.emplace_back(soundButton);

	// music on/off button (ví dụ)
	model = ResourceManager::GetInstance()->GetModel(0);
	normalTexture = ResourceManager::GetInstance()->GetTexture(25); // Thay bằng texture music button
	pressedTexture = ResourceManager::GetInstance()->GetTexture(26); // Thay bằng texture music button pressed
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> musicButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	musicButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 265.0f));
	musicButton->SetSize(150.0f, 45.0f);
	musicButton->SetOnClick([]() {
		printf("Music toggle clicked\n");
		// Thêm logic toggle music ở đây
		});
	m_gsSettingsGameButtons.emplace_back(musicButton);

	// back button để quay lại menu
	model = ResourceManager::GetInstance()->GetModel(0);
	normalTexture = ResourceManager::GetInstance()->GetTexture(23); // Thay bằng texture back button
	pressedTexture = ResourceManager::GetInstance()->GetTexture(24); // Thay bằng texture back button pressed
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> backButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	backButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 5, 395.0f));
	backButton->SetSize(150.0f, 45.0f);
	backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState(); // Quay lại state trước đó (menu)
		});
	m_gsSettingsGameButtons.emplace_back(backButton);

	printf("Settings init\n");
}

void GSSettings::Pause()
{
}

void GSSettings::Exit()
{
}

void GSSettings::Resume()
{
}

void GSSettings::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& x : m_gsSettingsObjects) {
		x->Draw();
	}
	for (auto& x : m_gsSettingsGameButtons) {
		x->Draw();
	}
}

void GSSettings::Update(float deltaTime)
{
	for (auto& x : m_gsSettingsObjects) {
		x->Update(deltaTime);
	}
	for (auto& x : m_gsSettingsGameButtons) {
		x->Update(deltaTime);
	}
}

void GSSettings::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	printf("gsSettingsKeyPressed: %c\n", key);

	// Có thể thêm phím tắt để quay lại menu
	if (key == 27 && bIsPressed) { // ESC key
		GameStateMachine::GetInstance()->PopState();
	}
}

void GSSettings::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	for (auto& btn : m_gsSettingsGameButtons) {
		btn->HandleTouchEvents(x, y, bIsPressed);
	}
}

void GSSettings::Cleanup()
{
}

GSSettings::~GSSettings()
{
}
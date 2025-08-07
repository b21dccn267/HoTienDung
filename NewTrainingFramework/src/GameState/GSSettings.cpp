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
	texture = ResourceManager::GetInstance()->GetTexture(18);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<Object> settingsBg = std::make_shared<Object>(model, texture, shader);
	settingsBg->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2 - 50));
	settingsBg->SetSize(321.0f, 404.0f);
	m_gsSettingsObjects.emplace_back(settingsBg);

	// sound on/off button
	model = ResourceManager::GetInstance()->GetModel(0);
	auto soundOnTexture = ResourceManager::GetInstance()->GetTexture(3);   // Sound ON texture
	auto soundOffTexture = ResourceManager::GetInstance()->GetTexture(17);  // Sound OFF texture
	shader = ResourceManager::GetInstance()->GetShader(0);
	m_soundButton = std::make_shared<GameButton>(model, soundOnTexture, soundOnTexture, shader);
	m_soundButton->Set2DPosition(Vector2(Globals::screenWidth / 2 - 40, 250.0f));
	m_soundButton->SetSize(50.0f, 50.0f);
	m_soundButton->SetOnClick([this]() {
		this->ToggleSound();
		});

	// Cập nhật texture để có cả sound on và sound off
	m_soundButton->SetNormalTexture(soundOnTexture);
	m_soundButton->SetPressedTexture(soundOnTexture); // Sử dụng cùng texture cho pressed state
	m_gsSettingsGameButtons.emplace_back(m_soundButton);

	// soundfx on/off button
	model = ResourceManager::GetInstance()->GetModel(0);
	auto soundfxOnTexture = ResourceManager::GetInstance()->GetTexture(3);   // SoundFX ON texture (thay số texture phù hợp)
	auto soundfxOffTexture = ResourceManager::GetInstance()->GetTexture(17);  // SoundFX OFF texture (thay số texture phù hợp)
	shader = ResourceManager::GetInstance()->GetShader(0);
	m_soundfxButton = std::make_shared<GameButton>(model, soundfxOnTexture, soundfxOnTexture, shader);
	m_soundfxButton->Set2DPosition(Vector2(Globals::screenWidth / 2 - 40, 320.0f));
	m_soundfxButton->SetSize(50.0f, 50.0f);
	m_soundfxButton->SetOnClick([this]() {
		this->ToggleSoundfx();
		});

	// Cập nhật texture để có cả soundfx on và soundfx off
	m_soundfxButton->SetNormalTexture(soundfxOnTexture);
	m_soundfxButton->SetPressedTexture(soundfxOnTexture); // Sử dụng cùng texture cho pressed state
	m_gsSettingsGameButtons.emplace_back(m_soundfxButton);

	// back button để quay lại menu
	model = ResourceManager::GetInstance()->GetModel(0);
	auto normalTexture = ResourceManager::GetInstance()->GetTexture(13);
	auto pressedTexture = ResourceManager::GetInstance()->GetTexture(14);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> backButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	backButton->Set2DPosition(Vector2(Globals::screenWidth / 2 - 40, 400.0f));
	backButton->SetSize(50.0f, 50.0f);
	backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_gsSettingsGameButtons.emplace_back(backButton);

	printf("Settings init\n");
}

void GSSettings::ToggleSound()
{
	m_soundEnabled = !m_soundEnabled;

	if (m_soundEnabled) {
		// Chuyển sang texture sound ON
		auto soundOnTexture = ResourceManager::GetInstance()->GetTexture(3);
		m_soundButton->SetNormalTexture(soundOnTexture);
		m_soundButton->SetPressedTexture(soundOnTexture);
		printf("Sound: ON\n");
	}
	else {
		// Chuyển sang texture sound OFF
		auto soundOffTexture = ResourceManager::GetInstance()->GetTexture(17);
		m_soundButton->SetNormalTexture(soundOffTexture);
		m_soundButton->SetPressedTexture(soundOffTexture);
		printf("Sound: OFF\n");
	}

	// bật/tắt sound
	// Ví dụ: AudioManager::GetInstance()->SetSoundEnabled(m_soundEnabled);
}

void GSSettings::ToggleSoundfx()
{
	m_soundfxEnabled = !m_soundfxEnabled;

	if (m_soundfxEnabled) {
		// Chuyển sang texture soundfx ON
		auto soundfxOnTexture = ResourceManager::GetInstance()->GetTexture(3);
		m_soundfxButton->SetNormalTexture(soundfxOnTexture);
		m_soundfxButton->SetPressedTexture(soundfxOnTexture);
		printf("SoundFX: ON\n");
	}
	else {
		// Chuyển sang texture soundfx OFF
		auto soundfxOffTexture = ResourceManager::GetInstance()->GetTexture(17);
		m_soundfxButton->SetNormalTexture(soundfxOffTexture);
		m_soundfxButton->SetPressedTexture(soundfxOffTexture);
		printf("SoundFX: OFF\n");
	}

	// bật/tắt soundfx
	// Ví dụ: AudioManager::GetInstance()->SetSoundfxEnabled(m_soundfxEnabled);
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
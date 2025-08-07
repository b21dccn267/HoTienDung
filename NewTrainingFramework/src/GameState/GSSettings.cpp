#include "GameButton.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameManager/SoundManager.h"
#include "GameObject/core/Object.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSSettings.h"

void GSSettings::Init()
{
	m_gsSettingsObjects.reserve(4);
	m_gsSettingsGameButtons.reserve(5);

	// Load button click sound effect nếu chưa có
	SoundManager::GetInstance()->LoadSfx("button_click", "../Resources/Sfx/vine-boom.wav");

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
	auto soundOffTexture = ResourceManager::GetInstance()->GetTexture(17); // Sound OFF texture
	shader = ResourceManager::GetInstance()->GetShader(0);

	// Khởi tạo button với trạng thái hiện tại từ SoundManager
	bool currentSoundState = SoundManager::GetInstance()->IsSoundEnabled();
	auto initialSoundTexture = currentSoundState ? soundOnTexture : soundOffTexture;

	m_soundButton = std::make_shared<GameButton>(model, initialSoundTexture, initialSoundTexture, shader);
	m_soundButton->Set2DPosition(Vector2(Globals::screenWidth / 2 - 40, 250.0f));
	m_soundButton->SetSize(50.0f, 50.0f);
	m_soundButton->SetOnClick([this]() {
		// Play button click sound (chỉ khi sound effects được bật)
		if (SoundManager::GetInstance()->IsSfxEnabled()) {
			SoundManager::GetInstance()->PlaySfx("button_click");
		}
		this->ToggleSound();
		});

	m_gsSettingsGameButtons.emplace_back(m_soundButton);

	// soundfx on/off button
	model = ResourceManager::GetInstance()->GetModel(0);
	auto soundfxOnTexture = ResourceManager::GetInstance()->GetTexture(3);   // SoundFX ON texture
	auto soundfxOffTexture = ResourceManager::GetInstance()->GetTexture(17); // SoundFX OFF texture
	shader = ResourceManager::GetInstance()->GetShader(0);

	// Khởi tạo button với trạng thái hiện tại từ SoundManager
	bool currentSfxState = SoundManager::GetInstance()->IsSfxEnabled();
	auto initialSfxTexture = currentSfxState ? soundfxOnTexture : soundfxOffTexture;

	m_soundfxButton = std::make_shared<GameButton>(model, initialSfxTexture, initialSfxTexture, shader);
	m_soundfxButton->Set2DPosition(Vector2(Globals::screenWidth / 2 - 40, 320.0f));
	m_soundfxButton->SetSize(50.0f, 50.0f);
	m_soundfxButton->SetOnClick([this]() {
		// Play button click sound trước khi toggle (chỉ khi còn được bật)
		if (SoundManager::GetInstance()->IsSfxEnabled()) {
			SoundManager::GetInstance()->PlaySfx("button_click");
		}
		this->ToggleSoundfx();
		});

	m_gsSettingsGameButtons.emplace_back(m_soundfxButton);

	// back button để quay lại menu
	model = ResourceManager::GetInstance()->GetModel(0);
	auto normalTexture = ResourceManager::GetInstance()->GetTexture(13);
	auto pressedTexture = ResourceManager::GetInstance()->GetTexture(14);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> backButton = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
	backButton->Set2DPosition(Vector2(Globals::screenWidth / 2 - 40, 400.0f));
	backButton->SetSize(50.0f, 50.0f);
	backButton->SetOnClick([this]() {
		// Play button click sound effect
		SoundManager::GetInstance()->PlaySfx("button_click");
		GameStateMachine::GetInstance()->PopState();
		});
	m_gsSettingsGameButtons.emplace_back(backButton);

	printf("Settings init with current sound states loaded\n");
}

void GSSettings::ToggleSound()
{
	// Lấy trạng thái hiện tại và đảo ngược nó
	bool newSoundState = !SoundManager::GetInstance()->IsSoundEnabled();

	// Cập nhật trạng thái trong SoundManager (điều này sẽ tự động pause/resume nhạc)
	SoundManager::GetInstance()->SetSoundEnabled(newSoundState);

	// Cập nhật texture của button để phản ánh trạng thái mới
	if (newSoundState) {
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
}

void GSSettings::ToggleSoundfx()
{
	// Lấy trạng thái hiện tại và đảo ngược nó
	bool newSfxState = !SoundManager::GetInstance()->IsSfxEnabled();

	// Cập nhật trạng thái trong SoundManager (điều này sẽ tự động stop các sound effects)
	SoundManager::GetInstance()->SetSfxEnabled(newSfxState);

	// Cập nhật texture của button để phản ánh trạng thái mới
	if (newSfxState) {
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
}

void GSSettings::Pause()
{
}

void GSSettings::Exit()
{
}

void GSSettings::Resume()
{
	// Khi resume settings, cập nhật lại texture của các button 
	// để đảm bảo chúng phản ánh đúng trạng thái hiện tại
	UpdateButtonTextures();
}

void GSSettings::UpdateButtonTextures()
{
	// Cập nhật sound button texture
	bool soundEnabled = SoundManager::GetInstance()->IsSoundEnabled();
	auto soundTexture = ResourceManager::GetInstance()->GetTexture(soundEnabled ? 3 : 17);
	if (m_soundButton) {
		m_soundButton->SetNormalTexture(soundTexture);
		m_soundButton->SetPressedTexture(soundTexture);
	}

	// Cập nhật sound fx button texture
	bool sfxEnabled = SoundManager::GetInstance()->IsSfxEnabled();
	auto sfxTexture = ResourceManager::GetInstance()->GetTexture(sfxEnabled ? 3 : 17);
	if (m_soundfxButton) {
		m_soundfxButton->SetNormalTexture(sfxTexture);
		m_soundfxButton->SetPressedTexture(sfxTexture);
	}
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
		SoundManager::GetInstance()->PlaySfx("button_click");
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
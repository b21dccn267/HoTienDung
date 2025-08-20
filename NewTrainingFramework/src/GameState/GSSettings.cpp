#include "GameButton.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameManager/SoundManager.h"
#include "GameObject/core/Object.h"
#include "GameStateMachine.h"
#include "GameObject/core/TextRenderer.h"
#include "GameObject/core/Texture.h"
#include "Globals.h"
#include "GSSettings.h"

void GSSettings::Init()
{
	m_gsSettingsObjects.reserve(10);
	m_gsSettingsGameButtons.reserve(8);

	// background
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(33);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<Object> background = std::make_shared<Object>(model, texture, shader);
	background->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	background->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_gsSettingsObjects.emplace_back(background);

	// Title text - Settings 
	auto textSettings = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("SETTING", "../Resources/Fonts/ChangaOne-Regular.ttf", 58)),
		ResourceManager::GetInstance()->GetShader(0));
	textSettings->Set2DPosition(Vector2(Globals::screenWidth / 2, 100.0f));
	textSettings->SetSize(400.0f, 120.0f);
	m_gsSettingsObjects.emplace_back(textSettings);


	// text - Music 
	auto textSound = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("Music")),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textSound->Set2DPosition(Vector2(Globals::screenWidth / 2 - 90, 320.0f));
	textSound->SetSize(100.0f, 50.0f);
	m_gsSettingsObjects.emplace_back(textSound);

	// Music decrease button (-)
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(35);  
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto musicDownButton = std::make_shared<GameButton>(model, texture, shader);
	musicDownButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 10, 320.0f));
	musicDownButton->SetSize(40.0f, 40.0f);
	musicDownButton->SetOnClick([this]() {
		DecreaseMusicVolume();
		});
	m_gsSettingsGameButtons.emplace_back(musicDownButton);

	// Music volume display 
	m_musicVolumeText = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("10")), // Placeholder
		ResourceManager::GetInstance()->GetShader(0)
	);
	m_musicVolumeText->Set2DPosition(Vector2(Globals::screenWidth / 2 + 60, 320.0f));
	m_musicVolumeText->SetSize(30.0f, 35.0f);
	m_gsSettingsObjects.emplace_back(m_musicVolumeText);

	// Music increase button (+)
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(34);  
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto musicUpButton = std::make_shared<GameButton>(model, texture, shader);
	musicUpButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 110, 320.0f));
	musicUpButton->SetSize(40.0f, 40.0f);
	musicUpButton->SetOnClick([this]() {
		IncreaseMusicVolume();
		});
	m_gsSettingsGameButtons.emplace_back(musicUpButton);


	// text - Soundfx 
	auto textSoundFX = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("Sound FX")),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textSoundFX->Set2DPosition(Vector2(Globals::screenWidth / 2 - 90, 390.0f));
	textSoundFX->SetSize(130.0f, 50.0f);
	m_gsSettingsObjects.emplace_back(textSoundFX);

	// SFX decrease button (-)
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(35); 
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto sfxDownButton = std::make_shared<GameButton>(model, texture, shader);
	sfxDownButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 10, 390.0f));
	sfxDownButton->SetSize(40.0f, 40.0f);
	sfxDownButton->SetOnClick([this]() {
		DecreaseSfxVolume();
		});
	m_gsSettingsGameButtons.emplace_back(sfxDownButton);

	// SFX volume display
	m_sfxVolumeText = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("10")), // Placeholder
		ResourceManager::GetInstance()->GetShader(0)
	);
	m_sfxVolumeText->Set2DPosition(Vector2(Globals::screenWidth / 2 + 60, 390.0f));
	m_sfxVolumeText->SetSize(30.0f, 35.0f);
	m_gsSettingsObjects.emplace_back(m_sfxVolumeText);

	// SFX increase button (+)
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(34);  
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto sfxUpButton = std::make_shared<GameButton>(model, texture, shader);
	sfxUpButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 110, 390.0f));
	sfxUpButton->SetSize(40.0f, 40.0f);
	sfxUpButton->SetOnClick([this]() {
		IncreaseSfxVolume();
		});
	m_gsSettingsGameButtons.emplace_back(sfxUpButton);

	// back button để quay lại menu
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(36);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> backButton = std::make_shared<GameButton>(model, texture, shader);
	backButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 420, 70.0f));
	backButton->SetSize(50.0f, 50.0f);
	backButton->SetOnClick([this]() {
		// Play button click sound effect
		SoundManager::GetInstance()->PlaySfx("button_click");
		GameStateMachine::GetInstance()->PopState();
		});
	m_gsSettingsGameButtons.emplace_back(backButton);

	UpdateVolumeDisplays();
}

void GSSettings::IncreaseMusicVolume()
{
	int currentVolume = SoundManager::GetInstance()->GetMusicVolume();
	int newVolume = currentVolume + 10; 
	if (newVolume > 100) newVolume = 100; 

	SoundManager::GetInstance()->SetMusicVolume(newVolume);
	UpdateVolumeDisplays();

	// Play sound effect để test volume
	SoundManager::GetInstance()->PlaySfx("button_click");
}

void GSSettings::DecreaseMusicVolume()
{
	int currentVolume = SoundManager::GetInstance()->GetMusicVolume();
	int newVolume = currentVolume - 10; 
	if (newVolume < 0) newVolume = 0; 

	SoundManager::GetInstance()->SetMusicVolume(newVolume);
	UpdateVolumeDisplays();

	// Play sound effect để test volume
	SoundManager::GetInstance()->PlaySfx("button_click");
}

void GSSettings::IncreaseSfxVolume()
{
	int currentVolume = SoundManager::GetInstance()->GetSfxVolume();
	int newVolume = currentVolume + 10; 
	if (newVolume > 100) newVolume = 100; 

	SoundManager::GetInstance()->SetSfxVolume(newVolume);
	UpdateVolumeDisplays();

	// Play sound effect để test volume mới
	SoundManager::GetInstance()->PlaySfx("button_click");
}

void GSSettings::DecreaseSfxVolume()
{
	int currentVolume = SoundManager::GetInstance()->GetSfxVolume();
	int newVolume = currentVolume - 10;
	if (newVolume < 0) newVolume = 0; 

	SoundManager::GetInstance()->SetSfxVolume(newVolume);
	UpdateVolumeDisplays();

	// Play sound effect để test volume mới
	SoundManager::GetInstance()->PlaySfx("button_click");
}

void GSSettings::UpdateVolumeDisplays()
{
	int musicVolume = SoundManager::GetInstance()->GetMusicVolume();
	int displayMusicVolume = musicVolume / 10;
	if (displayMusicVolume > 10) displayMusicVolume = 10;
	if (displayMusicVolume < 0) displayMusicVolume = 0;

	std::string musicVolumeStr = std::to_string(displayMusicVolume);
	auto musicTexture = std::make_shared<Texture>(TextRenderer::RenderText(musicVolumeStr.c_str()));
	m_musicVolumeText->m_pTexture = musicTexture;

	if (displayMusicVolume < 10) {
		m_musicVolumeText->SetSize(15.0f, 35.0f);
		m_musicVolumeText->Set2DPosition(Vector2(Globals::screenWidth / 2 + 60, 320.0f));
	}
	else {
		m_musicVolumeText->SetSize(30.0f, 35.0f);
		m_musicVolumeText->Set2DPosition(Vector2(Globals::screenWidth / 2 + 60, 320.0f));
	}

	int sfxVolume = SoundManager::GetInstance()->GetSfxVolume();
	int displaySfxVolume = sfxVolume / 10;
	if (displaySfxVolume > 10) displaySfxVolume = 10;
	if (displaySfxVolume < 0) displaySfxVolume = 0;

	std::string sfxVolumeStr = std::to_string(displaySfxVolume);
	auto sfxTexture = std::make_shared<Texture>(TextRenderer::RenderText(sfxVolumeStr.c_str()));
	m_sfxVolumeText->m_pTexture = sfxTexture;

	if (displaySfxVolume < 10) {
		m_sfxVolumeText->SetSize(15.0f, 35.0f);
		m_sfxVolumeText->Set2DPosition(Vector2(Globals::screenWidth / 2 + 60, 390.0f));
	}
	else {
		m_sfxVolumeText->SetSize(30.0f, 35.0f);
		m_sfxVolumeText->Set2DPosition(Vector2(Globals::screenWidth / 2 + 60, 390.0f));
	}

	printf("Music Volume: %d (Display: %d), SFX Volume: %d (Display: %d)\n",
		musicVolume, displayMusicVolume, sfxVolume, displaySfxVolume);
}

void GSSettings::Pause()
{
}

void GSSettings::Exit()
{
}

void GSSettings::Resume()
{
	UpdateVolumeDisplays();
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

	if (key == 27 && bIsPressed) { 
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
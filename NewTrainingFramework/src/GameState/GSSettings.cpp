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
	m_gsSettingsObjects.reserve(5);
	m_gsSettingsGameButtons.reserve(5);

	//// Load button click sound effect nếu chưa có
	//SoundManager::GetInstance()->LoadSfx("button_click", "../Resources/Sfx/vine-boom.wav");

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
		std::make_shared<Texture>(TextRenderer::RenderText("Settings")),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textSettings->Set2DPosition(Vector2(Globals::screenWidth / 2, 80.0f));
	textSettings->SetSize(400.0f, 100.0f);
	m_gsSettingsObjects.emplace_back(textSettings);

	// sound up button
	model = ResourceManager::GetInstance()->GetModel(0);
    texture = ResourceManager::GetInstance()->GetTexture(34);   
	shader = ResourceManager::GetInstance()->GetShader(0);
	m_soundButton = std::make_shared<GameButton>(model, texture, shader);
	m_soundButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 60, 300.0f));
	m_soundButton->SetSize(40.0f, 40.0f);
	m_gsSettingsGameButtons.emplace_back(m_soundButton);

	// text - Sound 
	auto textSound = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("Music")),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textSound->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, 300.0f));
	textSound->SetSize(100.0f, 50.0f);
	m_gsSettingsObjects.emplace_back(textSound);

	// soundfx up button
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(34);  
	shader = ResourceManager::GetInstance()->GetShader(0);
	m_soundfxButton = std::make_shared<GameButton>(model, texture, shader);
	m_soundfxButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 60, 370.0f));
	m_soundfxButton->SetSize(40.0f, 40.0f);
	m_gsSettingsGameButtons.emplace_back(m_soundfxButton);

	// text - Soundfx 
	auto textSoundFX = std::make_shared<Object>(
		ResourceManager::GetInstance()->GetModel(0),
		std::make_shared<Texture>(TextRenderer::RenderText("Sound FX")),
		ResourceManager::GetInstance()->GetShader(0)
	);
	textSoundFX->Set2DPosition(Vector2(Globals::screenWidth / 2 - 50, 370.0f));
	textSoundFX->SetSize(120.0f, 50.0f);
	m_gsSettingsObjects.emplace_back(textSoundFX);

	// sound down button 
	model = ResourceManager::GetInstance()->GetModel(0);
	auto soundUpTexture = ResourceManager::GetInstance()->GetTexture(35);
	shader = ResourceManager::GetInstance()->GetShader(0);

	std::shared_ptr<GameButton> soundUpButton = std::make_shared<GameButton>(model, soundUpTexture, soundUpTexture, shader);
	soundUpButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 110, 300.0f));
	soundUpButton->SetSize(40.0f, 40.0f);

	m_gsSettingsGameButtons.emplace_back(soundUpButton);

	// soundfx down button 
	model = ResourceManager::GetInstance()->GetModel(0);
	auto soundfxUpTexture = ResourceManager::GetInstance()->GetTexture(35);
	shader = ResourceManager::GetInstance()->GetShader(0);

	std::shared_ptr<GameButton> soundfxUpButton = std::make_shared<GameButton>(model, soundfxUpTexture, soundfxUpTexture, shader);
	soundfxUpButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 110, 370.0f));
	soundfxUpButton->SetSize(40.0f, 40.0f);

	m_gsSettingsGameButtons.emplace_back(soundfxUpButton);

	// back button để quay lại menu
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(36);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> backButton = std::make_shared<GameButton>(model, texture, shader);
	backButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 420, 70.0f));
	backButton->SetSize(50.0f,50.0f);
	backButton->SetOnClick([this]() {
		// Play button click sound effect
		SoundManager::GetInstance()->PlaySfx("button_click");
		GameStateMachine::GetInstance()->PopState();
		});
	m_gsSettingsGameButtons.emplace_back(backButton);

	printf("Settings init with current sound states loaded\n");
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
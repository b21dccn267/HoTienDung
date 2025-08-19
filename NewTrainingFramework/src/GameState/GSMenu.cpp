#include "GameButton.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameManager/SoundManager.h"
#include "GameObject/core/Object.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), m_isSoundOn(true)
{
}

void GSMenu::Init()
{
	m_gsMenuObjects.reserve(5);
	m_gsMenuGameButtons.reserve(5);

	// Khởi tạo SoundManager nếu chưa được khởi tạo
	SoundManager::GetInstance()->Init();

	// Lấy trạng thái sound hiện tại từ SoundManager
	m_isSoundOn = SoundManager::GetInstance()->IsSoundEnabled();

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = m_isSoundOn ?
		ResourceManager::GetInstance()->GetTexture(0) :   
		ResourceManager::GetInstance()->GetTexture(30);   
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	m_soundBg = std::make_shared<Object>(model, texture, shader);
	m_soundBg->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	m_soundBg->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_gsMenuObjects.emplace_back(m_soundBg);

	// play button
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(31);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> menuButton = std::make_shared<GameButton>(model, texture, shader);
	menuButton->Set2DPosition(Vector2(Globals::screenWidth / 2, 320.0f));
	menuButton->SetSize(150.0f, 85.0f);
	menuButton->SetOnClick([]() {
		// Play button click sound nếu sound được bật
		if (SoundManager::GetInstance()->IsSoundEnabled()) {
			SoundManager::GetInstance()->PlaySfx("button_click");
		}
		GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
		});
	m_gsMenuGameButtons.emplace_back(menuButton);

	// settings button
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(31);
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> settingsButton = std::make_shared<GameButton>(model, texture, shader);
	settingsButton->Set2DPosition(Vector2(Globals::screenWidth / 2 + 420, 630.0f));
	settingsButton->SetSize(60.0f, 80.0f);
	settingsButton->SetOnClick([]() {
		// Play button click sound nếu sound được bật
		if (SoundManager::GetInstance()->IsSoundEnabled()) {
			SoundManager::GetInstance()->PlaySfx("button_click");
		}
		GameStateMachine::GetInstance()->PushState(StateType::STATE_SETTINGS);
		});
	m_gsMenuGameButtons.emplace_back(settingsButton);

	// invisible sound toggle button 
	model = ResourceManager::GetInstance()->GetModel(0);
	auto emptyTexture = ResourceManager::GetInstance()->GetTexture(31); 
	shader = ResourceManager::GetInstance()->GetShader(0);
	std::shared_ptr<GameButton> soundToggleButton = std::make_shared<GameButton>(model, emptyTexture, shader);
	soundToggleButton->Set2DPosition(Vector2(60.0f, 632.0f));
	soundToggleButton->SetSize(60.0f, 75.0f);

	soundToggleButton->SetOnClick([this]() {
		ToggleSound();
		});
	m_gsMenuGameButtons.emplace_back(soundToggleButton);

	// Load sound effects và music cho menu
	SoundManager::GetInstance()->LoadSfx("button_click", "../Resources/Sfx/vine-boom.wav");
	SoundManager::GetInstance()->LoadMusic("menu_music", "../Resources/Sfx/Stalemate.wav");

	// Bắt đầu phát nhạc nền menu nếu sound được bật
	if (SoundManager::GetInstance()->IsSoundEnabled()) {
		SoundManager::GetInstance()->PlayMusic("menu_music", -1);
	}
}

void GSMenu::ToggleSound()
{
	m_isSoundOn = !m_isSoundOn;

	// Cập nhật SoundManager với trạng thái mới - chỉ cần gọi SetSoundEnabled
	SoundManager::GetInstance()->SetSoundEnabled(m_isSoundOn);

	// Nếu bật lại sound và chưa có nhạc nào chạy, phát nhạc menu
	if (m_isSoundOn) {
		if (!Mix_PlayingMusic()) {
			SoundManager::GetInstance()->PlayMusic("menu_music", -1);
		}
	}

	// Thay đổi texture của background dựa trên trạng thái sound
	if (m_isSoundOn) {
		auto soundOnTexture = ResourceManager::GetInstance()->GetTexture(0);
		m_soundBg->m_pTexture = soundOnTexture;
	}
	else {
		auto soundOffTexture = ResourceManager::GetInstance()->GetTexture(30);
		m_soundBg->m_pTexture = soundOffTexture;
	}
}

void GSMenu::Pause()
{
	// Pause nhạc nền khi menu bị tạm dừng
	if (SoundManager::GetInstance()->IsSoundEnabled()) {
		SoundManager::GetInstance()->PauseMusic();
	}
}

void GSMenu::Exit()
{
	// Stop nhạc nền khi thoát khỏi menu
	SoundManager::GetInstance()->StopMusic();
}

void GSMenu::Resume()
{
	// Cập nhật trạng thái sound khi quay lại menu
	m_isSoundOn = SoundManager::GetInstance()->IsSoundEnabled();

	// Resume nhạc nền nếu sound được bật
	if (m_isSoundOn) {
		// Kiểm tra xem có nhạc nào đang bị pause không
		if (Mix_PausedMusic()) {
			SoundManager::GetInstance()->ResumeMusic();
		}
		// Nếu không có nhạc nào đang chạy và sound được bật, bắt đầu phát nhạc menu
		else if (!Mix_PlayingMusic()) {
			SoundManager::GetInstance()->PlayMusic("menu_music", -1);
		}
	}

	// Cập nhật texture background cho phù hợp
	if (m_isSoundOn) {
		auto soundOnTexture = ResourceManager::GetInstance()->GetTexture(0);
		m_soundBg->m_pTexture = soundOnTexture;
	}
	else {
		auto soundOffTexture = ResourceManager::GetInstance()->GetTexture(30);
		m_soundBg->m_pTexture = soundOffTexture;
	}
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
	// Stop nhạc nền khi cleanup
	SoundManager::GetInstance()->StopMusic();
}

GSMenu::~GSMenu()
{
}
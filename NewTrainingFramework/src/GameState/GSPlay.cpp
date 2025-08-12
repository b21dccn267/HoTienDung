#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameManager/SoundManager.h"
#include "GameObject/core/Animation.h"
#include "GameObject/core/TextRenderer.h"
#include "GameObject/core/Texture.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSPlay.h"
#include <SDL2/SDL_mixer.h>

void GSPlay::Init()
{
    m_gsPlayObjects.reserve(1);
    m_gsPlayButtons.reserve(2);

    // Khởi tạo Creature và Init nó
    m_creature = std::make_shared<Creature>();
    m_creature->Init();  // QUAN TRỌNG: Phải gọi Init() để setup texture và animation
    m_creature->Idle();  // Bắt đầu với animation idle

    // Load nhạc nền cho state play nếu chưa được load
    SoundManager::GetInstance()->LoadMusic("background_music", "../Resources/Sfx/Stalemate.wav");

    // Load sound effects cho các action trong game
    SoundManager::GetInstance()->LoadSfx("button_click", "../Resources/Sfx/vine-boom.wav");
    SoundManager::GetInstance()->LoadSfx("move_sound", "../Resources/Sfx/vine-boom.wav");

    //background
    auto model = ResourceManager::GetInstance()->GetModel(0);
    auto texture = ResourceManager::GetInstance()->GetTexture(0);  // Sound on background texture ID
    auto shader = ResourceManager::GetInstance()->GetShader(0);
    auto playBg = std::make_shared<Object>(model, texture, shader);
    playBg->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
    playBg->SetSize(Globals::screenWidth, Globals::screenHeight);
    m_gsPlayObjects.emplace_back(playBg);

    // pause button
    model = ResourceManager::GetInstance()->GetModel(0);
    auto normalTexture = ResourceManager::GetInstance()->GetTexture(25);   // Texture cho pause button nổi
    auto pressedTexture = ResourceManager::GetInstance()->GetTexture(19);  // Texture cho pause button chìm 
    shader = ResourceManager::GetInstance()->GetShader(0);
    auto btnPause = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
    btnPause->Set2DPosition(Vector2(Globals::screenWidth - 100, 100.0f));
    btnPause->SetSize(60.0f, 60.0f);
    btnPause->SetOnClick([this]() {
        // Play button click sound effect
        SoundManager::GetInstance()->PlaySfx("button_click");
        GameStateMachine::GetInstance()->PushState(StateType::STATE_PAUSE);
        });
    m_gsPlayButtons.emplace_back(btnPause);

    // Bắt đầu phát nhạc nền khi khởi tạo state play
    // Chỉ phát nếu chưa có nhạc nào đang chạy hoặc không phải nhạc nền này
    if (!Mix_PlayingMusic()) {
        SoundManager::GetInstance()->PlayMusic("background_music", -1); // -1 = loop vô hạn
    }
    printf("Play state initialized with background music\n");
}

void GSPlay::Pause()
{
    m_isPaused = true;
    // Pause nhạc nền khi game bị tạm dừng
    SoundManager::GetInstance()->PauseMusic();
}

void GSPlay::Exit()
{
    // Stop nhạc nền khi thoát khỏi state play
    SoundManager::GetInstance()->StopMusic();
}

void GSPlay::Resume()
{
    m_isPaused = false;
    // Resume nhạc nền khi quay lại game
    SoundManager::GetInstance()->ResumeMusic();
}

void GSPlay::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto& x : m_gsPlayObjects) {
        x->Draw();
    }

    // Vẽ creature trước khi vẽ UI (buttons)
    if (m_creature) {
        m_creature->Draw();
    }

    for (auto& x : m_gsPlayButtons) {
        x->Draw();
    }
}

void GSPlay::Update(float deltaTime)
{
    if (m_isPaused) {
        return; // Không cập nhật khi game bị tạm dừng
    }

    for (auto& x : m_gsPlayObjects) {
        x->Update(deltaTime);
    }

    if (m_creature) {
        m_creature->Update(deltaTime); // Cập nhật animation và hitbox
        m_creature->Update2DPosition(); // Cập nhật vị trí
    }

    for (auto& x : m_gsPlayButtons) {
        x->Update(deltaTime);
    }
}

void GSPlay::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
    printf("gsPlayKeyPressed: %c\n", key);
    if (bIsPressed && m_creature) {
        // Lưu vị trí hiện tại để kiểm tra bounds
        float currentX = m_creature->m_anim->m_position.x;
        float currentY = m_creature->m_anim->m_position.y;
        float newX = currentX;
        float newY = currentY;

        switch (key) {
        case 0x57: // W - Move Up
            newY = currentY - 50.0f;  // Tăng bước di chuyển
            if (newY >= 50.0f) {  // Kiểm tra bounds
                m_creature->m_anim->m_position.y = newY;
                m_creature->LookUp();  // Đổi animation
                SoundManager::GetInstance()->PlaySfx("move_sound");
            }
            break;
        case 0x41: // A - Move Left
            newX = currentX - 50.0f;
            if (newX >= 50.0f) {  // Kiểm tra bounds
                m_creature->m_anim->m_position.x = newX;
                m_creature->LookLeft();  // Đổi animation
                SoundManager::GetInstance()->PlaySfx("move_sound");
            }
            break;
        case 0x53: // S - Move Down
            newY = currentY + 50.0f;
            if (newY <= Globals::screenHeight - 50.0f) {  // Kiểm tra bounds
                m_creature->m_anim->m_position.y = newY;
                m_creature->LookDown();  // Đổi animation
                SoundManager::GetInstance()->PlaySfx("move_sound");
            }
            break;
        case 0x44: // D - Move Right
            newX = currentX + 50.0f;
            if (newX <= Globals::screenWidth - 50.0f) {  // Kiểm tra bounds
                m_creature->m_anim->m_position.x = newX;
                m_creature->LookRight();  // Đổi animation
                SoundManager::GetInstance()->PlaySfx("move_sound");
            }
            break;
        case 0x20: // Space - Jump/Idle animation
            m_creature->Jump();
            SoundManager::GetInstance()->PlaySfx("move_sound");
            break;
        }
    }

    // Trở về idle animation sau 1 khoảng thời gian (có thể implement timer)
    // Hoặc có thể để cho CreatureController xử lý
}

void GSPlay::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
    printf("gsPlayMouseEvent\n");

    // Xử lý button clicks trước
    for (auto& btn : m_gsPlayButtons) {
        if (btn->HandleTouchEvents(x, y, bIsPressed)) {
            return;
        }
    }

    // Nếu không click vào button nào, có thể di chuyển creature đến vị trí click
    if (bIsPressed && m_creature) {
        // Di chuyển creature đến vị trí click (tùy chọn)
        m_creature->m_anim->m_position.x = (float)x;
        m_creature->m_anim->m_position.y = (float)y;

        // Determine direction and set appropriate animation
        float deltaX = x - m_creature->m_anim->m_position.x;
        float deltaY = y - m_creature->m_anim->m_position.y;

        if (abs(deltaX) > abs(deltaY)) {
            if (deltaX > 0) m_creature->LookRight();
            else m_creature->LookLeft();
        }
        else {
            if (deltaY > 0) m_creature->LookDown();
            else m_creature->LookUp();
        }

        SoundManager::GetInstance()->PlaySfx("move_sound");
    }
}

void GSPlay::Cleanup()
{
    SoundManager::GetInstance()->StopMusic();
    // Cleanup creature if needed
    if (m_creature) {
        m_creature.reset();
    }
}

GSPlay::~GSPlay()
{
}
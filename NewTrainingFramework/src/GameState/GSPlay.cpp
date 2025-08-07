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

    // Khởi tạo Creature riêng biệt
    m_creature = std::make_shared<Creature>();

    // pause
    auto model = ResourceManager::GetInstance()->GetModel(0);
    auto normalTexture = ResourceManager::GetInstance()->GetTexture(25);   // Texture cho pause button nổi
    auto pressedTexture = ResourceManager::GetInstance()->GetTexture(19);  // Texture cho pause button chìm 
    auto shader = ResourceManager::GetInstance()->GetShader(0);
    auto btnPause = std::make_shared<GameButton>(model, normalTexture, pressedTexture, shader);
    btnPause->Set2DPosition(Vector2(Globals::screenWidth - 100, 100.0f));
    btnPause->SetSize(60.0f, 60.0f);
    btnPause->SetOnClick([]() {
        GameStateMachine::GetInstance()->PushState(StateType::STATE_PAUSE);
        });

    m_gsPlayButtons.emplace_back(btnPause);

    printf("play init\n");
}

void GSPlay::Pause()
{
    m_isPaused = true;
}

void GSPlay::Exit()
{
}

void GSPlay::Resume()
{
    m_isPaused = false;
}

void GSPlay::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto& x : m_gsPlayObjects) {
        x->Draw();
    }
    for (auto& x : m_gsPlayButtons) {
        x->Draw();
    }
    if (m_creature) {
        m_creature->Draw(); // Vẽ Creature trực tiếp
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
    for (auto& x : m_gsPlayButtons) {
        x->Update(deltaTime);
    }
    if (m_creature) {
        m_creature->Update(deltaTime); // Cập nhật Creature trực tiếp
        m_creature->Update2DPosition();
    }
}

void GSPlay::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
    printf("gsPlayKeyPresed: %c\n", key);
    if (bIsPressed && m_creature) {
        switch (key) {
        case 0x57: // W
            m_creature->m_anim->m_position.y -= 10.0f;
            break;
        case 0x41: // A
            m_creature->m_anim->m_position.x -= 10.0f;
            break;
        case 0x53: // S
            m_creature->m_anim->m_position.y += 10.0f;
            break;
        case 0x44: // D
            m_creature->m_anim->m_position.x += 10.0f;
            break;
        }
    }
}

void GSPlay::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
    printf("gsPlayMouseEvent\n");
    for (auto& btn : m_gsPlayButtons) {
        if (btn->HandleTouchEvents(x, y, bIsPressed)) {
            return;
        }
    }
}

void GSPlay::Cleanup()
{
}

GSPlay::~GSPlay()
{
}
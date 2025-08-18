#include "../../Utilities/utilities.h"
#include "GameManager/InputManager.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameManager/SoundManager.h"
#include "GameObject/actors/AmogusGunner.h"
#include "GameObject/actors/hero/CrHero.h"
#include "GameObject/actors/Skeleton.h"
#include "GameObject/core/Animation.h"
#include "GameObject/core/TextRenderer.h"
#include "GameObject/core/Texture.h"
#include "GameObject/items/weapons/Sword.h"
#include "GameObject/ui/WndUpgrade.h"
#include "GameObject/utils/CreatureController.h"
#include "GameObject/utils/Timer.h"
#include "GameState/GameButton.h" 
#include "GameStateMachine.h"
#include "Globals.h"
#include "GSPlay.h"
#include "GSGameOver.h"
#include <SDL2/SDL_mixer.h>

void GSPlay::Init()
{
    m_isInGladiatorMode = false;

    SoundManager::GetInstance()->LoadMusic("background_music", "../Resources/Sfx/Stalemate.wav");
    SoundManager::GetInstance()->LoadSfx("button_click", "../Resources/Sfx/button_click.wav");
    SoundManager::GetInstance()->LoadSfx("move_sound", "../Resources/Sfx/vine-boom.wav");

    // background
    auto model = ResourceManager::GetInstance()->GetModel(0);
    auto texture = ResourceManager::GetInstance()->GetTexture(33);  
    auto shader = ResourceManager::GetInstance()->GetShader(0);
    auto playBg = std::make_shared<Object>(model, texture, shader);
    playBg->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
    playBg->SetSize(Globals::screenWidth, Globals::screenHeight);
    m_gsPlayObjects.emplace_back(playBg);

    // actors
    m_hero = std::make_shared<Hero>();
    m_hero->Init();
    m_hero->LookDown();

    m_hero2 = std::make_shared<CrHero>();
    m_hero2->Init();
    m_hero2->LookDown();

    m_creatureSpawner = std::make_shared<CreatureSpawner>();

    // hud
    m_healthBar1 = std::make_shared<HealthBar>(200, 50);
    m_healthBar2 = std::make_shared<HealthBar>(700, 50);

    m_healthBar1->m_health = m_hero->m_health;
    m_healthBar2->m_health = m_hero2->m_health;

    m_timer = std::make_shared<Timer>();
    m_timer->StartTimer(60);
    m_upgradeMenu = std::make_shared<WndUpgrade>();
    m_upgradeMenu->m_isActive = true;


    // pause button
    model = ResourceManager::GetInstance()->GetModel(0);
    texture = ResourceManager::GetInstance()->GetTexture(25);
    shader = ResourceManager::GetInstance()->GetShader(0);
    auto btnPause = std::make_shared<GameButton>(model, texture, shader);
    btnPause->Set2DPosition(Vector2(Globals::screenWidth - 100, 100.0f));
    btnPause->SetSize(60.0f, 60.0f);
    btnPause->SetOnClick([this]() {

        if (SoundManager::GetInstance()->IsSoundEnabled()) {
            SoundManager::GetInstance()->PlaySfx("button_click");
        }
        GameStateMachine::GetInstance()->PushState(StateType::STATE_PAUSE);
        });
    m_gsPlayButtons.emplace_back(btnPause);


    SoundManager::GetInstance()->PlayMusicIfEnabled("background_music", -1);
    printf("Play state initialized\n");
}

void GSPlay::Pause()
{
    m_isPaused = true;
    if (SoundManager::GetInstance()->IsSoundEnabled()) {
        SoundManager::GetInstance()->PauseMusic();
    }
}

void GSPlay::Exit()
{
    SoundManager::GetInstance()->StopMusic();
}

void GSPlay::Resume()
{
    m_isPaused = false;
    // Resume nhạc nền khi quay lại game (chỉ khi sound được bật)
    if (SoundManager::GetInstance()->IsSoundEnabled()) {
        // Kiểm tra xem có nhạc nào đang bị pause không
        if (Mix_PausedMusic()) {
            SoundManager::GetInstance()->ResumeMusic();
        }
        // Nếu không có nhạc nào đang chạy và sound được bật, bắt đầu phát
        else if (!Mix_PlayingMusic()) {
            SoundManager::GetInstance()->PlayMusic("background_music", -1);
        }
    }
}


void GSPlay::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& x : m_gsPlayObjects) {
        x->Draw();
    }

    // actors
    m_hero->Draw();
    m_hero2->Draw();
    for (auto& x : m_creatureSpawner->m_creatureActive) {
        x->Draw();
    }

    // hud
    m_healthBar1->Draw();
    m_healthBar2->Draw();
    m_timer->m_displayText->Draw();
    if (m_upgradeMenu->m_isActive) {
        m_upgradeMenu->Draw();
    }
   

    for (auto& x : m_gsPlayButtons) {
        x->Draw();
    }
}

void GSPlay::Update(float deltaTime)
{
    //// remove this later
    m_upgradeMenu->m_isActive = false;
    //
    if (m_isPaused) {
        return;
    }

    for (auto& x : m_gsPlayObjects) {
        x->Update(deltaTime);
    }

    // wasd
    if (InputManager::GetInstance()->keys[0x57]) {
        m_hero->m_anim->m_position.y -= 130.0f * deltaTime;
        m_hero->LookUp();
    }
    if (InputManager::GetInstance()->keys[0x41]) {
        m_hero->m_anim->m_position.x -= 130.0f * deltaTime;
        m_hero->LookLeft();
    }
    if (InputManager::GetInstance()->keys[0x53]) {
        m_hero->m_anim->m_position.y += 130.0f * deltaTime;
        m_hero->LookDown();
    }
    if (InputManager::GetInstance()->keys[0x44]) {
        m_hero->m_anim->m_position.x += 130.0f * deltaTime;
        m_hero->LookRight();
    }
    if (InputManager::GetInstance()->keys[0x41] &&
        InputManager::GetInstance()->keys[0x57]) {
        m_hero->LookTopLeft();
    }
    if (InputManager::GetInstance()->keys[0x44] &&
        InputManager::GetInstance()->keys[0x57]) {
        m_hero->LookTopRight();
    }
    if (InputManager::GetInstance()->keys[0x41] &&
        InputManager::GetInstance()->keys[0x53]) {
        m_hero->LookBottomLeft();
    }
    if (InputManager::GetInstance()->keys[0x44] &&
        InputManager::GetInstance()->keys[0x53]) {
        m_hero->LookBottomRight();
    }
    // arrows
    if (InputManager::GetInstance()->keys[0x26]) {
        m_hero2->m_anim->m_position.y -= 130.0f * deltaTime;
        m_hero2->LookUp();
    }
    if (InputManager::GetInstance()->keys[0x25]) {
        m_hero2->m_anim->m_position.x -= 130.0f * deltaTime;
        m_hero2->LookLeft();
        m_hero2->m_isLookingLeft = true;
    }
    if (InputManager::GetInstance()->keys[0x28]) {
        m_hero2->m_anim->m_position.y += 130.0f * deltaTime;
        m_hero2->LookDown();
    }
    if (InputManager::GetInstance()->keys[0x27]) {
        m_hero2->m_anim->m_position.x += 130.0f * deltaTime;
        m_hero2->LookRight();
        m_hero2->m_isLookingLeft = false;
    }
    if (InputManager::GetInstance()->keys[0x25] &&
        InputManager::GetInstance()->keys[0x26]) {
        m_hero2->LookTopLeft();
    }
    if (InputManager::GetInstance()->keys[0x27] &&
        InputManager::GetInstance()->keys[0x26]) {
        m_hero2->LookTopRight();
    }
    if (InputManager::GetInstance()->keys[0x25] &&
        InputManager::GetInstance()->keys[0x28]) {
        m_hero2->LookBottomLeft();
    }
    if (InputManager::GetInstance()->keys[0x27] &&
        InputManager::GetInstance()->keys[0x28]) {
        m_hero2->LookBottomRight();
    }
    // sword attack
    if (InputManager::GetInstance()->keys[0x20]) {
        if (m_hero2->m_sword->m_isOnCooldown == false) {
            m_hero2->m_sword->UseSword(Vector2(m_hero2->m_anim->m_position.x, m_hero2->m_anim->m_position.y), m_hero2->m_isLookingLeft);
        }
    }


    if (m_creatureSpawner->m_isOnCooldown == false) {
        m_creatureSpawner->SpawnCreature();
        m_creatureSpawner->m_isOnCooldown = true;
    }


    if (InputManager::GetInstance()->m_mouseIsPressed == true
        && InputManager::GetInstance()->m_timerIsActive == false
        ) {
        printf("bang\n");
        InputManager::GetInstance()->m_timerIsActive = true;
        m_hero->m_gun->m_fMouseX = InputManager::GetInstance()->m_mouseX;
        m_hero->m_gun->m_fMouseY = InputManager::GetInstance()->m_mouseY;
        m_hero->FireGun();
    }

    if (InputManager::GetInstance()->m_timerIsActive == true) {
        InputManager::GetInstance()->m_timeSincePressed += deltaTime;
        if (InputManager::GetInstance()->m_timeSincePressed > 0.75f) {
            InputManager::GetInstance()->m_timerIsActive = false;
            InputManager::GetInstance()->m_timeSincePressed = 0.0f;
        }
    }


    m_hero->Update(deltaTime);
    m_hero->Update2DPosition();
    m_hero2->Update(deltaTime);
    m_hero2->Update2DPosition();

    m_creatureSpawner->Update(deltaTime, m_hero, m_hero2, m_isInGladiatorMode);

    //printf("%f %f\n", m_hero->m_anim->m_position.x, m_hero->m_anim->m_position.y);

    m_healthBar1->UpdateHealth(m_hero->m_health);
    m_healthBar2->UpdateHealth(m_hero2->m_health);
    m_timer->UpdateTimer(deltaTime);
    m_upgradeMenu->Update(InputManager::GetInstance()->m_mouseX,
                          InputManager::GetInstance()->m_mouseY,
                          InputManager::GetInstance()->m_mouseIsPressed
    );


    for (auto& x : m_gsPlayButtons) {
        x->Update(deltaTime);
    }


    // checking special event triggers, upgrade menu appear flags and stuff
    if (m_timer->m_time % 15 == 0 && m_timer->m_time < 60) {
        m_isInGladiatorMode = true;
    }
    else {
        //m_upgradeMenu->m_isActive = true;
        //m_isInGladiatorMode = true;
    }

    if (m_isInGladiatorMode) {
        //printf("battle\n");
        // do stuff here, such as:
        // no spawning creatures
        // friendly fire on
    }

    if (m_timer->m_time <= 0.0f) {
        GSGameOver::s_pendingCustomText = "Time's Up!"; // Set text trước
        GameStateMachine::GetInstance()->PushState(StateType::STATE_GAMEOVER);
        return;
    }
}

void GSPlay::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
    //printf("0x%02X\n", key);
    InputManager::GetInstance()->keys[key] = bIsPressed;
}

void GSPlay::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
    //printf("%d %d\n", InputManager::GetInstance()->m_mouseX, InputManager::GetInstance()->m_mouseY);

    InputManager::GetInstance()->m_mouseX = x;
    InputManager::GetInstance()->m_mouseY = y;
    InputManager::GetInstance()->m_mouseIsPressed = bIsPressed;

    // fix this to use InputManager
    for (auto& btn : m_gsPlayButtons) {
        if (btn->HandleTouchEvents(x, y, bIsPressed)) {
            return;
        }
    }
}

void GSPlay::Cleanup()
{
    SoundManager::GetInstance()->StopMusic();
}

GSPlay::~GSPlay()
{
}
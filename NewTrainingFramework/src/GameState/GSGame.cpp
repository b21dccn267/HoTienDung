#include "GameManager/InputManager.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameManager/SoundManager.h"
#include "GameObject/core/Animation.h"
#include "GameObject/core/TextRenderer.h"
#include "GameObject/utils/CreatureController.h"
#include "GameObject/actors/Skeleton.h"
#include "GSGame.h"
#include <Globals.h>


void GSGame::Init()
{
	// should have actor postioning here instead of in class
	m_hero = std::make_shared<Hero>();
	m_hero->Init();
	m_hero->LookBottomRight();

	m_hero2 = std::make_shared<Creature>();
	m_hero2->LookLeft();

	m_creatureSpawner = std::make_shared<CreatureSpawner>();

	// hud
	m_healthBar1 = std::make_shared<HealthBar>(200, 50);
	m_healthBar2 = std::make_shared<HealthBar>(700, 50);

	m_healthBar1->m_health = m_hero->m_health;
	m_healthBar2->m_health = m_hero2->m_health;

	printf("game init\n");
}

void GSGame::Pause()
{
}

void GSGame::Exit()
{
}

void GSGame::Resume()
{
}

void GSGame::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_hero->Draw();
	m_hero2->Draw();
	for (auto& x : m_creatureSpawner->m_creatureActive) {
		x->Draw();
	}

	// hud
	m_healthBar1->Draw();
	m_healthBar2->Draw();
}

void GSGame::Update(float deltaTime)
{
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
	}
	if (InputManager::GetInstance()->keys[0x28]) {
		m_hero2->m_anim->m_position.y += 130.0f * deltaTime;
		m_hero2->LookDown();
	}
	if (InputManager::GetInstance()->keys[0x27]) {
		m_hero2->m_anim->m_position.x += 130.0f * deltaTime;
		m_hero2->LookRight();
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

	m_creatureSpawner->Update(deltaTime, m_hero, m_hero2);

	//printf("%f %f\n", m_hero->m_anim->m_position.x, m_hero->m_anim->m_position.y);

	m_healthBar1->UpdateHealth(m_hero->m_health);
	m_healthBar2->UpdateHealth(m_hero2->m_health);
}

void GSGame::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	//printf("0x%02X\n", key);
	InputManager::GetInstance()->keys[key] = bIsPressed;
}

void GSGame::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	//printf("%d %d\n", InputManager::GetInstance()->m_mouseX, InputManager::GetInstance()->m_mouseY);

	InputManager::GetInstance()->m_mouseX = x;
	InputManager::GetInstance()->m_mouseY = y;
	InputManager::GetInstance()->m_mouseIsPressed = bIsPressed;
}

void GSGame::Cleanup()
{
}

GSGame::~GSGame()
{
}
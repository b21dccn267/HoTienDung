#include "GSGame.h"
#include "Globals.h"
#include "GameManager/InputManager.h"
#include "GameManager/SceneManager.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SoundManager.h"
#include "GameObject/core/TextRenderer.h"
#include "GameObject/core/Animation.h"


void GSGame::Init()
{
	// should have actor postioning here instead of in class
	m_hero = std::make_shared<Hero>();
	m_hero->LookBottomRight();

	m_creature = std::make_shared<Creature>();
	m_creature->LookLeft();

	m_creatureSpawner = std::make_shared<CreatureSpawner>();
	m_creatureSpawner->SpawnCreature();
	
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
	m_creature->Draw();
	for (auto& x : m_creatureSpawner->m_creatures) {
		x->Draw();
	}
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
		m_creature->m_anim->m_position.y -= 130.0f * deltaTime;
		m_creature->LookUp();
	}
	if (InputManager::GetInstance()->keys[0x25]) {
		m_creature->m_anim->m_position.x -= 130.0f * deltaTime;
		m_creature->LookLeft();
	}
	if (InputManager::GetInstance()->keys[0x28]) {
		m_creature->m_anim->m_position.y += 130.0f * deltaTime;
		m_creature->LookDown();
	}
	if (InputManager::GetInstance()->keys[0x27]) {
		m_creature->m_anim->m_position.x += 130.0f * deltaTime;
		m_creature->LookRight();
	}

	m_hero->Update(deltaTime);
	m_hero->Update2DPosition();
	m_creature->Update(deltaTime);
	m_creature->Update2DPosition();
	for (auto& x : m_creatureSpawner->m_creatures) {
		x->Update(deltaTime);
	}
}

void GSGame::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	InputManager::GetInstance()->keys[key] = bIsPressed;
}

void GSGame::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	printf("gsGameMouseEvent\n");
	if (bIsPressed) {
		m_hero->FireGun();
	}
}

void GSGame::Cleanup()
{
}

GSGame::~GSGame()
{
}

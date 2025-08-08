#include "GSGame.h"
#include <Globals.h>
#include <GameManager/InputManager.h>
#include <GameManager/SceneManager.h>
#include <GameManager/ResourceManager.h>
#include <GameManager/SoundManager.h>
#include <GameObject/core/TextRenderer.h>
#include <GameObject/core/Animation.h>
#include <GameObject/utils/CreatureController.h>


void GSGame::Init()
{
	// should have actor postioning here instead of in class
	m_hero = std::make_shared<Hero>();
	m_hero->Init();
	m_hero->LookBottomRight();

	m_creature = std::make_shared<Creature>();
	m_creature->LookLeft();

	m_creatureSpawner = std::make_shared<CreatureSpawner>();

	m_creatureSpawner->SpawnCreature();
	//m_creatureSpawner->SpawnCreature();
	//m_creatureSpawner->SpawnCreature();
	
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
	if (InputManager::GetInstance()->keys[0x25] &&
		InputManager::GetInstance()->keys[0x26]) {
		m_creature->LookTopLeft();
	}
	if (InputManager::GetInstance()->keys[0x27] &&
		InputManager::GetInstance()->keys[0x26]) {
		m_creature->LookTopRight();
	}
	if (InputManager::GetInstance()->keys[0x25] &&
		InputManager::GetInstance()->keys[0x28]) {
		m_creature->LookBottomLeft();
	}
	if (InputManager::GetInstance()->keys[0x27] &&
		InputManager::GetInstance()->keys[0x28]) {
		m_creature->LookBottomRight();
	}

	// test die anim
	//if (InputManager::GetInstance()->keys[0x4A]) {
	//	m_creature->Die();
	//}

	// test skeleton, remove creature keys b4 proceeding
	//if (InputManager::GetInstance()->keys[0x26]) {
	//	m_creatureSpawner->m_creatures[0]->m_anim->m_position.y -= 130.0f * deltaTime;
	//	m_creatureSpawner->m_creatures[0]->LookUp();
	//}
	//if (InputManager::GetInstance()->keys[0x25]) {
	//	m_creatureSpawner->m_creatures[0]->m_anim->m_position.x -= 130.0f * deltaTime;
	//	m_creatureSpawner->m_creatures[0]->LookLeft();
	//}
	//if (InputManager::GetInstance()->keys[0x28]) {
	//	m_creatureSpawner->m_creatures[0]->m_anim->m_position.y += 130.0f * deltaTime;
	//	m_creatureSpawner->m_creatures[0]->LookDown();
	//}
	//if (InputManager::GetInstance()->keys[0x27]) {
	//	m_creatureSpawner->m_creatures[0]->m_anim->m_position.x += 130.0f * deltaTime;
	//	m_creatureSpawner->m_creatures[0]->LookRight();
	//}
	//if (InputManager::GetInstance()->keys[0x25] &&
	//	InputManager::GetInstance()->keys[0x26]) {
	//	m_creatureSpawner->m_creatures[0]->LookTopLeft();
	//}
	//if (InputManager::GetInstance()->keys[0x27] &&
	//	InputManager::GetInstance()->keys[0x26]) {
	//	m_creatureSpawner->m_creatures[0]->LookTopRight();
	//}
	//if (InputManager::GetInstance()->keys[0x25] &&
	//	InputManager::GetInstance()->keys[0x28]) {
	//	m_creatureSpawner->m_creatures[0]->LookBottomLeft();
	//}
	//if (InputManager::GetInstance()->keys[0x27] &&
	//	InputManager::GetInstance()->keys[0x28]) {
	//	m_creatureSpawner->m_creatures[0]->LookBottomRight();
	//}


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
		//printf("blocking further fires for %f sec\n", InputManager::GetInstance()->m_timeSincePressed);
		InputManager::GetInstance()->m_timeSincePressed += deltaTime;
		if (InputManager::GetInstance()->m_timeSincePressed > 0.75f) {
			InputManager::GetInstance()->m_timerIsActive = false;
			InputManager::GetInstance()->m_timeSincePressed = 0.0f;
			//printf("stopped blocking\n");
		}
	}


	m_hero->Update(deltaTime);
	m_hero->Update2DPosition();
	m_creature->Update(deltaTime);
	m_creature->Update2DPosition();
	for (auto& x : m_creatureSpawner->m_creatures) {
		x->m_control->Move(deltaTime, Vector2(m_hero->m_anim->m_position.x, m_hero->m_anim->m_position.y));
		x->Update2DPosition();
		x->Update(deltaTime);
	}
}

void GSGame::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	printf("0x%02X\n", key);
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

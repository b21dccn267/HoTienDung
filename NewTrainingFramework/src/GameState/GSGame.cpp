#include "stdafx.h"
#include "GSGame.h"
#include "Globals.h"
#include "../GameManager/SceneManager.h"
#include "../GameManager/ResourceManager.h"
#include "../GameManager/SoundManager.h"
#include "../GameObject/core/TextRenderer.h"
#include "../GameObject/core/Animation.h"


void GSGame::Init()
{
	// should have actor postioning here instead of in class
	m_hero = std::make_shared<Hero>();
	m_creature = std::make_shared<Creature>();
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
	//for (auto& x : m_gsGameObject) {
	//	x->Draw();
	//}
	//m_gsGameObject->Draw();
	m_hero->Draw();
	m_creature->Draw();
}

void GSGame::Update(float deltaTime)
{
	//m_gsGameObject->Update(deltaTime);
	m_hero->Update(deltaTime);
	m_hero->Update2DPosition();
	m_creature->Update(deltaTime);
	m_creature->Update2DPosition();
}

void GSGame::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	printf("gsgameKeyPresed: 0x%02X\n", key);
	//SoundManager::PlaySfx("../Resources/Sfx/vine-boom.wav");
	if (bIsPressed) {
		switch (key) {
		case 0x57:
			m_hero->m_anim->m_position.y -= 10.0f;
			break;
		case 0x41:
			m_hero->m_anim->m_position.x -= 10.0f;
			break;
		case 0x53:
			m_hero->m_anim->m_position.y += 10.0f;
			break;
		case 0x44:
			m_hero->m_anim->m_position.x += 10.0f;
			break;
		// arrow keys
		//case 0x26:
		//	m_creature->m_anim->m_position.y -= 10.0f;
		//	break;
		//case 0x25:
		//	m_creature->m_anim->m_position.x -= 10.0f;
		//	break;
		//case 0x28:
		//	m_creature->m_anim->m_position.y += 10.0f;
		//	break;
		//case 0x27:
		//	m_creature->m_anim->m_position.x += 10.0f;
		//	break;
		}
	}
}

void GSGame::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	printf("gsGameMouseEvent\n");
	if (bIsPressed) {
		//m_hero->m_gun->Fire();
		m_hero->FireGun();
	}
}

void GSGame::Cleanup()
{
}

GSGame::~GSGame()
{
}

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
	//auto model = ResourceManager::GetInstance()->GetModel(0);
	//auto texture = ResourceManager::GetInstance()->GetTexture(5);
	//auto shader = ResourceManager::GetInstance()->GetShader(1);
	//auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 3);
	//anim->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	//anim->SetSize(100, 100);

	//m_gsGameObject = anim;
	m_hero->Init();
	m_creature->Init();
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
	m_creature->Update(deltaTime);
}

void GSGame::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	printf("gsgameKeyPresed: %c\n", key);
	//SoundManager::PlaySfx("../Resources/Sfx/vine-boom.wav");
	if (bIsPressed) {
		switch (key) {
		case 0x57:
			//printf("W pressed\n");
			//m_gsPlayAnimations[0]->m_position.y -= 10.0f;
			break;
		case 0x41:
			//printf("A pressed\n");
			//m_gsPlayAnimations[0]->m_position.x -= 10.0f;
			break;
		case 0x53:
			//printf("S pressed\n");
			//m_gsPlayAnimations[0]->m_position.y += 10.0f;
			break;
		case 0x44:
			//printf("D pressed\n");
			//m_gsPlayAnimations[0]->m_position.x += 10.0f;
			break;
		}
	}
}

void GSGame::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
}

void GSGame::Cleanup()
{
}

GSGame::~GSGame()
{
}

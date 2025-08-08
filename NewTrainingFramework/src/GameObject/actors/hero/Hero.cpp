#include "Hero.h"
#include <Globals.h>
#include <GameManager/ResourceManager.h>
#include <GameObject/core/Animation.h>
#include <GameObject/items/weapons/Gun.h>
#include <vector>

Hero::Hero()
{
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(9);
	auto shader = ResourceManager::GetInstance()->GetShader(2);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 0);
	anim->m_numFramesPerRow = 9;
	anim->m_numFramesPerColumn = 7;
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2 - 100, Globals::screenHeight / 2));
	anim->SetSize(100, 100);

	m_anim = anim;
}

void Hero::Init()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_gun = std::make_shared<Gun>(weak_from_this());
	m_gun->Init();
}

void Hero::Idle()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::Jump()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{20, 21, 22, 23, 24, 25, 26, 27});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookUp()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{12, 13, 14, 15});
	m_anim->m_frameTime = 0.12f;
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookDown() // same as idle, fix this
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookTopRight()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{16, 17, 18, 19});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookTopLeft()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{16, 17, 18, 19});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 3.14f, 0));
}

void Hero::LookRight()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{8, 9, 10, 11});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookLeft()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{8, 9, 10, 11});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 3.14f, 0));
}

void Hero::LookBottomRight()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{4, 5, 6, 7});
	m_anim->SetRotation(Vector3(0, 180 *(3.14f/180.0f), 0));
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookBottomLeft()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(9);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{4, 5, 6, 7});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 3.14f, 0));
}

void Hero::Die()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(7);

	m_anim->m_numFramesPerRow = 3;
	m_anim->m_numFramesPerColumn = 2;
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3, 4, 5});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::Draw()
{
	m_anim->CustomDraw();

	m_gun->Draw();
}

void Hero::Update(GLfloat deltaTime)
{
	m_anim->CustomUpdate(deltaTime);

	m_gun->Update(deltaTime);
}

void Hero::Update2DPosition()
{
	m_anim->Set2DPosition(Vector2(m_anim->m_position.x, m_anim->m_position.y));
}

void Hero::FireGun()
{
	m_gun->Fire();
}

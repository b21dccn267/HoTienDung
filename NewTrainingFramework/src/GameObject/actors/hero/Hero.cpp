
#include "Hero.h"
#include "../../../Globals.h"
#include "../../../GameManager/ResourceManager.h"
#include "../../core/Animation.h"
#include "../../items/weapons/Gun.h"
#include <vector>

Hero::Hero()
{
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(9);
	auto shader = ResourceManager::GetInstance()->GetShader(2);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 0);
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2 - 100, Globals::screenHeight / 2));
	anim->SetSize(100, 100);
	//anim->SetRotation(Vector3(0,3.14, 0));
	//anim->SetCustomFrames(std::vector<int>{9, 10, 11, 12});

	m_anim = anim;

	//m_gun = std::make_shared<Gun>();
	//m_gun = std::make_shared<Gun>(shared_from_this());
	m_gun = std::make_shared<Gun>(weak_from_this());
}

void Hero::Idle()
{
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::Jump()
{
	m_anim->SetCustomFrames(std::vector<int>{20, 21, 22, 23, 24, 25, 26, 27});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookUp()
{
	m_anim->SetCustomFrames(std::vector<int>{12, 13, 14, 15});
	m_anim->m_frameTime = 0.12f;
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookDown() // same as idle, fix this
{
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookTopRight()
{
	m_anim->SetCustomFrames(std::vector<int>{16, 17, 18, 19});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookTopLeft()
{
	m_anim->SetCustomFrames(std::vector<int>{16, 17, 18, 19});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void Hero::LookRight()
{
	m_anim->SetCustomFrames(std::vector<int>{8, 9, 10, 11});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookLeft()
{
	m_anim->SetCustomFrames(std::vector<int>{8, 9, 10, 11});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void Hero::LookBottomRight()
{
	m_anim->SetCustomFrames(std::vector<int>{4, 5, 6, 7});
	m_anim->SetRotation(Vector3(0, 180 *(3.14/180), 0));
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Hero::LookBottomLeft()
{
	m_anim->SetCustomFrames(std::vector<int>{4, 5, 6, 7});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void Hero::Draw()
{
	//m_anim->Draw();
	m_anim->CustomDraw();
	if (m_gun->m_isActive) {
		//m_gun->m_projectile->Draw();
	}
}

void Hero::Update(GLfloat deltaTime)
{
	//m_anim->Update(deltaTime);
	m_anim->CustomUpdate(deltaTime);
	if (m_gun->m_isActive) {
		m_gun->Update(deltaTime);
	}
}

void Hero::Update2DPosition()
{
	m_anim->Set2DPosition(Vector2(m_anim->m_position.x, m_anim->m_position.y));
	if (m_gun->m_isActive) {
		//m_gun->m_projectile->Set2DPosition(Vector2(m_gun->m_projectile->m_position.x, m_gun->m_projectile->m_position.y));
	}
}

void Hero::FireGun()
{
	m_gun->Fire();
	//m_belongings->FireWeapon();
}

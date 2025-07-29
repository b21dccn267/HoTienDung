#include "stdafx.h"
#include "Hero.h"
#include "Globals.h"
#include "../../GameManager/ResourceManager.h"

Hero::Hero()
{
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(5);
	auto shader = ResourceManager::GetInstance()->GetShader(1);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 1);
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2 - 100, Globals::screenHeight / 2));
	anim->SetSize(100, 100);
	m_anim = anim;

	m_gun = std::make_shared<Gun>();
}

void Hero::Draw()
{
	m_anim->Draw();
	if (m_gun->m_isActive) {
		m_gun->m_projectile->Draw();
	}
}

void Hero::Update(GLfloat deltaTime)
{
	m_anim->Update(deltaTime);
	if (m_gun->m_isActive) {
		m_gun->Update(deltaTime);
	}
}

void Hero::Update2DPosition()
{
	m_anim->Set2DPosition(Vector2(m_anim->m_position.x, m_anim->m_position.y));
	if (m_gun->m_isActive) {
		m_gun->m_projectile->Set2DPosition(Vector2(m_gun->m_projectile->m_position.x, m_gun->m_projectile->m_position.y));
	}
}

void Hero::FireGun()
{
	m_gun->Fire();
}

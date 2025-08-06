#include "GameManager/ResourceManager.h"
#include "GameObject/items/weapons/Gun.h"
#include "GameObject/actors/hero/Hero.h"
#include "Globals.h"
#include "Projectile.h"
#include <memory>

//class Gun;

Projectile::Projectile(std::weak_ptr<Gun> owner)
{
	this->m_owner = owner;

	this->m_pModel = ResourceManager::GetInstance()->GetModel(0);
	this->m_pTexture = ResourceManager::GetInstance()->GetTexture(6);
	this->m_pShader = ResourceManager::GetInstance()->GetShader(0);
	this->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	this->SetSize(100, 100);
	m_fTimePassed = 0.0f;
}

void Projectile::SetProjectile(Vector2 startPos)
{
	this->Set2DPosition(startPos);
	//this->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	//m_fTimePassed = 0.0f;
}

void Projectile::Update(GLfloat deltaTime, float x, float y) 
{
	// this function should not take in any args other than deltaTime
	// all coords should be given to each projectile in acquire()

	// get access to Hero pos
	auto owner = m_owner.lock();
	auto ownerOwner = owner->m_owner.lock();

	float ratio = x / y;
	float deltaMoveX = x - ownerOwner->m_anim->m_position.x;
	float deltaMoveY = y - ownerOwner->m_anim->m_position.y;

	//m_fTimePassed += deltaTime;
	m_position.x += deltaMoveX * deltaTime;
	m_position.y += deltaMoveY * deltaTime;

	this->Set2DPosition(Vector2(m_position.x, m_position.y));
}
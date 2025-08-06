#include "Projectile.h"
#include "Globals.h"
#include "GameManager/ResourceManager.h"
#include <memory>

class Gun;

Projectile::Projectile(std::weak_ptr<Gun> owner)
{
	this->owner = owner;

	this->m_pModel = ResourceManager::GetInstance()->GetModel(0);
	this->m_pTexture = ResourceManager::GetInstance()->GetTexture(6);
	this->m_pShader = ResourceManager::GetInstance()->GetShader(0);
	this->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	this->SetSize(100, 100);
	m_fTimePassed = 0.0f;
}

void Projectile::SetProjectile()
{
	this->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	m_fTimePassed = 0.0f;
}

void Projectile::Update(GLfloat deltaTime, float x, float y)
{
	float ratio = x / y;
	printf("flying...\n");
	m_fTimePassed += deltaTime;
	m_position.x += 200.0f * deltaTime;
	m_position.y += 200.0f * deltaTime * ratio;
	this->Set2DPosition(Vector2(m_position.x, m_position.y));
	
}
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

	//this->m_pModel = ResourceManager::GetInstance()->GetModel(0);
	//this->m_pTexture = ResourceManager::GetInstance()->GetTexture(6);
	//this->m_pShader = ResourceManager::GetInstance()->GetShader(0);
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(6);
	auto shader = ResourceManager::GetInstance()->GetShader(2);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 0);
	anim->m_numFramesPerRow = 4;
	anim->m_numFramesPerColumn = 1;
	
	//anim->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	anim->SetSize(40, 40);
	m_fTimePassed = 0.0f;
	
	m_anim = anim;
}

void Projectile::ProjLoop()
{
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 0, 0));
}

void Projectile::SetProjectile(Vector2 startPos, Vector2 endPos)
{
	this->m_startPos = startPos;
	this->m_endPos = endPos;
	this->Set2DPosition(startPos);
	auto owner = m_owner.lock();
	auto ownerOwner = owner->m_owner.lock();


	// calculate direction of mouse and player.
	Vector3 mousPos = Vector3(owner->m_fMouseX, owner->m_fMouseY, 0);
	Vector3 playerPos = Vector3(ownerOwner->m_anim->m_position.x, ownerOwner->m_anim->m_position.y, 0);
	//printf("ownerOwner->m_anim->m_position.x = %f, ownerOwner->m_anim->m_position.y = %f", ownerOwner->m_anim->m_position.x, ownerOwner->m_anim->m_position.y);
	direction = (mousPos - playerPos).Normalize();

}

void Projectile::Update(GLfloat deltaTime) 
{
	m_anim->CustomUpdate(deltaTime);
	// this function should not take in any args other than deltaTime
	// all coords should be given to each projectile in acquire()

	// get access to Hero pos
	

	//float ratio = x / y;
	//float deltaMoveX = x - ownerOwner->m_anim->m_position.x;
	//float deltaMoveY = y - ownerOwner->m_anim->m_position.y;
//	deltaMoveX = owner->m_fMouseX - ownerOwner->m_anim->m_position.x;
   // deltaMoveY = owner->m_fMouseY - ownerOwner->m_anim->m_position.y;


	m_position.x += direction.x * m_velocity * deltaTime;
	m_position.y += direction.y *m_velocity * deltaTime;

	m_anim->Set2DPosition(Vector2(m_position.x, m_position.y));
}



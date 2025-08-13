#include "GameManager/ResourceManager.h"
#include "GameObject/items/weapons/Gun.h"
#include "GameObject/actors/hero/Hero.h"
#include "GameObject/utils/AABB.h"
#include "Globals.h"
#include "Projectile.h"
#include <memory>


Projectile::Projectile()
{
	//this->m_owner = owner;

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(6);
	auto shader = ResourceManager::GetInstance()->GetShader(2);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 0);
	anim->m_numFramesPerRow = 4;
	anim->m_numFramesPerColumn = 1;
	
	anim->SetSize(40, 40);
	m_fTimePassed = 0.0f;
	
	m_anim = anim;

	m_hitbox = std::make_shared<AABB>();
	m_hitbox->UpdateBox(Vector2(m_anim->m_position.x, m_anim->m_position.y), Vector2(m_anim->m_iWidth, m_anim->m_iHeight));
}

void Projectile::ProjLoop()
{
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
}

void Projectile::SetProjectile(Vector3 startPos, Vector3 endPos)
{
	//this->m_startPos = startPos;
	//this->m_endPos = endPos;
	this->Set2DPosition(Vector2(startPos.x, startPos.y));
	//auto owner = m_owner;
	//auto ownerOwner = owner->m_owner;// .lock();


	// calculate direction of mouse and player.
	//Vector3 mousPos = Vector3(owner->m_fMouseX, owner->m_fMouseY, 0);
//	Vector3 playerPos = Vector3(ownerOwner->m_anim->m_position.x, ownerOwner->m_anim->m_position.y, 0);
	//printf("ownerOwner->m_anim->m_position.x = %f, ownerOwner->m_anim->m_position.y = %f", ownerOwner->m_anim->m_position.x, ownerOwner->m_anim->m_position.y);
	direction = (endPos - startPos).Normalize();

}

void Projectile::Update(GLfloat deltaTime) 
{
	m_anim->CustomUpdate(deltaTime);
	m_hitbox->UpdateBox(Vector2(m_anim->m_position.x, m_anim->m_position.y), Vector2(m_anim->m_iWidth, m_anim->m_iHeight));

	m_position.x += direction.x * m_velocity * deltaTime;
	m_position.y += direction.y *m_velocity * deltaTime;

	m_anim->Set2DPosition(Vector2(m_position.x, m_position.y));
}
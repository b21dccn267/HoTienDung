#include "Skeleton.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/utils/CreatureController.h"
#include <vector>


Skeleton::Skeleton() : Creature()
{
	m_creatureType = 0;

	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
	m_isDie = false;
}

void Skeleton::Jump()
{
	Creature::Jump();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::LookUp()
{
	Creature::LookUp();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::LookDown() // same as idle, fix this
{
	Creature::LookDown();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::LookTopRight()
{
	Creature::LookTopRight();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::LookTopLeft()
{
	Creature::LookTopLeft();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::LookRight()
{
	Creature::LookRight();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::LookLeft()
{
	Creature::LookLeft();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::LookBottomRight()
{
	Creature::LookBottomRight();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::LookBottomLeft()
{
	Creature::LookBottomLeft();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::Idle()
{
	Creature::Idle();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::Die()
{
	Creature::Die();
}

void Skeleton::Move(float deltaTime, Vector2 heroPos)
{
	Creature::Move(deltaTime, heroPos);
}

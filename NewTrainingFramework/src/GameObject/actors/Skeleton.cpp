#include "Skeleton.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/utils/CreatureController.h"
#include <vector>
#include "Globals.h"
#include "GameObject/utils/AABB.h"


Skeleton::Skeleton() : Creature()
{
	m_creatureType = 0;
	m_isDie = false;

	// creature init
	m_isMoveLeft = false;
	m_isMoveRight = false;
	m_isMoveUp = false;
	m_isMoveDown = false;

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(12);
	auto shader = ResourceManager::GetInstance()->GetShader(2);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 1);
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	anim->SetSize(100, 100);
	//anim->SetCustomFrames(std::vector<int>{20, 21, 22, 23});
	m_anim = anim;

	m_hitbox = std::make_shared<AABB>();
	m_hitbox->UpdateBox(Vector2(m_anim->m_position.x, m_anim->m_position.y), Vector2(m_anim->m_iWidth, m_anim->m_iHeight));

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{20, 21, 22, 23});
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

void Skeleton::Draw()
{
	Creature::Draw();
}

void Skeleton::Update(float deltaTime)
{
	Creature::Update(deltaTime);
}

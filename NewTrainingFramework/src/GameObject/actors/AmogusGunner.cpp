#include "AmogusGunner.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/items/weapons/CreatureGun.h"
#include "GameObject/utils/AABB.h"
#include "GameObject/utils/CreatureController.h"
#include "Globals.h"
#include <memory>
#include <vector>

AmogusGunner::AmogusGunner() : Creature()
{

}

void AmogusGunner::Init()
{
	m_creatureType = 1;
	m_isMoveLeft = false;
	m_isMoveRight = false;
	m_isMoveUp = false;
	m_isMoveDown = false;

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(42);
	auto shader = ResourceManager::GetInstance()->GetShader(2);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 1);
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	anim->SetSize(100, 100);
	anim->m_numFramesPerRow = 4;
	anim->m_numFramesPerColumn = 1;
	m_anim = anim;

	m_hitbox = std::make_shared<AABB>();
	m_hitbox->UpdateBox(Vector2(m_anim->m_position.x, m_anim->m_position.y), Vector2(m_anim->m_iWidth, m_anim->m_iHeight));

	m_isOnCooldown = false;
	m_cooldownTimer = 0.0f;
	m_cooldown = 3.0f;
	m_canMove = true;

	m_crGun = std::make_shared<CreatureGun>();
	m_crGun->Init();
}

void AmogusGunner::LookRight()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(42);

	m_anim->m_numFramesPerRow = 4;
	m_anim->m_numFramesPerColumn = 1;
	m_anim->SetCustomFrames(std::vector<int>{24, 25, 26, 27});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void AmogusGunner::LookLeft()
{
	AmogusGunner::LookRight();
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void AmogusGunner::ShootAnimRight()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(37);

	m_anim->m_numFramesPerRow = 4;
	m_anim->m_numFramesPerColumn = 1;
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void AmogusGunner::ShootAnimLeft()
{
	AmogusGunner::ShootAnimRight();
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void AmogusGunner::Idle()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(42);
	m_anim->m_numFramesPerRow = 4;
	m_anim->m_numFramesPerColumn = 1;
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void AmogusGunner::Die()
{
	Creature::Die();
}

// for gunner this function also decides firing behavior
void AmogusGunner::Move(float deltaTime, Vector2 heroPos)
{
	// fix this to stop upon reaching a certain spot on the map
	if ((std::abs(heroPos.x - this->m_anim->m_position.x) > 50.0f 
		//&& std::abs(heroPos.y - this->m_anim->m_position.x) > 100.0f
		)
		&& m_canMove == true) {
		Creature::Move(deltaTime, heroPos);
	}
	else {
		m_canMove = false;
		if (!m_isOnCooldown) {
			m_crGun->CrFire(Vector2(m_anim->m_position.x, m_anim->m_position.y), heroPos);
			m_isOnCooldown = true;
		}
	}
}

void AmogusGunner::Draw()
{
	m_anim->CustomDraw();
	m_crGun->Draw();
}

void AmogusGunner::Update(float deltaTime)
{
	Creature::Update(deltaTime);
	m_crGun->Update(deltaTime);

	if (m_isOnCooldown == true) {
		m_cooldownTimer += deltaTime;
		if (m_cooldownTimer > m_cooldown) {
			m_isOnCooldown = false;
			m_cooldownTimer = 0.0f;
		}
	}
}

bool AmogusGunner::DoDerived(std::shared_ptr<AABB> hitbox)
{
	for (auto& x : m_crGun->m_projectileUsed) {
		if (AABB::IsCollideRR(x->m_hitbox, hitbox)) {
			x->m_anim->Set2DPosition(Vector2(-1000, -1000)); // ensures its removed
			return true;
		}
	}
	return false;
}

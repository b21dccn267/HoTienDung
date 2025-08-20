#include "Sword.h"
#include <memory>
#include "GameManager/ResourceManager.h"
#include "GameObject/utils/AABB.h"
#include "GameObject/core/Animation.h"


Sword::Sword()
{
	m_isActive = false;
	m_isOnCooldown = false;
	m_cooldownTimer = 0.0f;
	m_cooldown = 1.0f;

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(45);
	auto shader = ResourceManager::GetInstance()->GetShader(2);
	m_anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 0);
	m_anim->Set2DPosition(Vector2(0, 0)); // bind to hero pos later
	m_anim->SetSize(200, 50);
	m_anim->m_numFramesPerColumn = 1;
	m_anim->m_numFramesPerRow = 3;
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2});
	m_anim->m_frameTime = 0.12f;

	m_hitbox = std::make_shared<AABB>();
}

void Sword::UseSword(Vector2 pos, bool isLookingLeft)
{
	// cooldown check in gsPlay
	m_isActive = true;
	m_isOnCooldown = true;
	if (isLookingLeft) {
		m_anim->Set2DPosition(Vector2(pos.x - 90.0f, pos.y));
		m_anim->SetRotation(Vector3(0, 3.14f, 0));
		m_hitbox->UpdateBox(Vector2(m_anim->m_position.x, m_anim->m_position.y), Vector2(m_anim->m_iWidth * 2, m_anim->m_iHeight));
	}
	else {
		m_anim->Set2DPosition(Vector2(pos.x + 90.0f, pos.y));
		m_anim->SetRotation(Vector3(0, 0, 0));
		m_hitbox->UpdateBox(Vector2(m_anim->m_position.x, m_anim->m_position.y), Vector2(m_anim->m_iWidth * 2, m_anim->m_iHeight));
	}
}

// hero will call this in its draw()
void Sword::Draw()
{
	if (m_isActive) {
		m_anim->CustomDraw(); 
	}
}

void Sword::Update(float deltaTime)
{
	if (m_isActive) {
		m_anim->CustomUpdate(deltaTime);
	}

	if (m_anim->m_frameCount == 2) {
		m_isActive = false;
		m_hitbox->UpdateBox(Vector2(-100, -100), Vector2(-100, -100));
		m_anim->m_frameCount = 0;
	}

	// cooldown independent of casting
	if (m_isOnCooldown == true) {
		m_cooldownTimer += deltaTime;
		if (m_cooldownTimer > m_cooldown) {
			m_isOnCooldown = false;
			m_cooldownTimer = 0.0f;
		}
	}
}

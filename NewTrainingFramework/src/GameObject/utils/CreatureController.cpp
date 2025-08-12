#include "CreatureController.h"

CreatureController::CreatureController()
{
	//this->m_owner = owner;
}

void CreatureController::Move(float deltaTime, Vector2 heroPos)
{
	//if (m_cooldownIsActive) {
	//	m_timeSinceSpawn += deltaTime;
	//	if (m_timeSinceSpawn > 0.5f) {
	//		m_cooldownIsActive = false;
	//	}
	//}
	//else {
	//	//auto owner = m_owner.lock();

	//	if (m_owner->m_anim->m_position.x <= heroPos.x) {
	//		m_owner->m_anim->m_position.x += 5.0f;
	//	}
	//	else {
	//		m_owner->m_anim->m_position.x -= 5.0f;
	//	}
	//	if (m_owner->m_anim->m_position.y <= heroPos.y) {
	//		m_owner->m_anim->m_position.y += 5.0f;
	//	}
	//	else {
	//		m_owner->m_anim->m_position.y -= 5.0f;
	//	}

	//	m_timeSinceSpawn = 0.0f;
	//	m_cooldownIsActive = true;
	//}
}

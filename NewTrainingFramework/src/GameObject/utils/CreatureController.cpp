#include "CreatureController.h"

CreatureController::CreatureController(std::weak_ptr<Creature> owner)
{
	this->m_owner = owner;
}

void CreatureController::Move(float deltaTime, Vector2 heroPos)
{
	if (m_cooldownIsActive) {
		m_timeSinceSpawn += deltaTime;
		if (m_timeSinceSpawn > 0.5f) {
			m_cooldownIsActive = false;
		}
	}
	else {
		auto owner = m_owner.lock();

		if (owner->m_anim->m_position.x <= heroPos.x) {
			owner->m_anim->m_position.x += 5.0f;
		}
		else {
			owner->m_anim->m_position.x -= 5.0f;
		}
		if (owner->m_anim->m_position.y <= heroPos.y) {
			owner->m_anim->m_position.y += 5.0f;
		}
		else {
			owner->m_anim->m_position.y -= 5.0f;
		}

		m_timeSinceSpawn = 0.0f;
		m_cooldownIsActive = true;
	}
}

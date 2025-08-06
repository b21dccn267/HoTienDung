#include "CreatureController.h"

CreatureController::CreatureController(std::weak_ptr<Creature> owner)
{
	this->m_owner = owner;
}

void CreatureController::Move()
{
	auto owner = m_owner.lock();
	owner->m_anim->m_position.x += 10.0f;
	owner->m_anim->m_position.y += 10.0f;
	//owner->m_anim->Set2DPosition(Vector2(owner->m_anim->m_position.x+10.0f, owner->m_anim->m_position.y+10.0f));
}

#pragma once
#include "GameObject/actors/Creature.h"
#include <memory>


// this class manages enemy ai
class CreatureController
{
public:
	std::weak_ptr<Creature> m_owner;

	bool m_cooldownIsActive = false;
	float m_timeSinceSpawn = 0.0f;

	CreatureController(std::weak_ptr<Creature> owner);
	void Move(float deltaTime, Vector2 heroPos);
};


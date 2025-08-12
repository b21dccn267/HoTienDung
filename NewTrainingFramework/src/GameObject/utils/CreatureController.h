#pragma once
#include "GameObject/actors/Creature.h"
#include <memory>

class SpriteAnimation;
// this class manages enemy ai
class CreatureController 
{
public:
//	std::shared_ptr<Creature> m_owner;

	bool m_cooldownIsActive = false;
	float m_timeSinceSpawn = 0.0f;

	CreatureController();
	void Move(float deltaTime, Vector2 heroPos);
};


#pragma once
#include "GameObject/core/Object.h"
#include <memory>

class Animation;
class AABB;

// new weapon for hero
// spawns an object with hitbox representing sword hit 
// is literally the whip, only shit either left or right
class Sword
{
public:
	//std::shared_ptr<Object> m_self;
	std::shared_ptr<Animation> m_anim;
	std::shared_ptr<AABB> m_hitbox;
	bool m_isActive;
	bool m_isOnCooldown;
	float m_cooldownTimer;
	float m_cooldown;

	Sword();
	void UseSword(Vector2 pos, bool isLookingLeft);
	void Draw();
	void Update(float deltaTime);
};


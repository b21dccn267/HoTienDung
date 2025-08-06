#pragma once
#include "GameObject/core/Object.h"
#include "GameManager/ResourceManager.h"

#include <memory>

class Gun;
// an actor, spawns when gun is fired
// delete self when reaching max range
// add projectile hit creature
//		if self coord = creature coord -> call function isHit to creature holder obj of game state -> deduct hp (isHit int, > 3 = die())
class Projectile : public Object
{
public:
	std::weak_ptr<Gun> m_owner;

	//float m_moveSpeed = 50.0f;
	int m_id;

	Projectile(std::weak_ptr<Gun> owner);

	// have projectile fly autonomously, but uses flyValue and isActive for texture display
	void SetProjectile(Vector2 startPos);
	void Update(GLfloat deltaTime, float x, float y);
	float m_fTimePassed;
	float m_velocity = 10.0f;
};


#pragma once
#include "../core/Object.h"
#include "../../GameManager/ResourceManager.h"
#include <memory>


// an actor, spawns when gun is fired
// delete self when reaching max range
// add projectile hit creature
//		if self coord = creature coord -> call function isHit to creature holder obj of game state -> deduct hp (isHit int, > 3 = die())
class Projectile : public Object
{
public:
	int m_id;

	float m_moveSpeed = 50.0f;

	Projectile();
	~Projectile() {};
	// have projectile fly autonomously, but uses flyValue and isActive for texture display
	void SetProjectile();
	void Update(GLfloat deltaTime);
	float m_fTimePassed;
	bool m_isActive;
};


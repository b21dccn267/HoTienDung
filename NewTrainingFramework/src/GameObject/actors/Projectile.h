#pragma once
#include "GameObject/core/Object.h"
#include "GameManager/ResourceManager.h"
//#include "utilities.h"
#include "../../Utilities/utilities.h"
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

	
	int m_id;
	Vector2 m_startPos;
	Vector2 m_endPos;
	float m_moveSpeed = 50.0f;

	Projectile(std::weak_ptr<Gun> owner);

	// have projectile fly autonomously, but uses flyValue and isActive for texture display
	void SetProjectile(Vector2 startPos, Vector2 endPos);
	void Update(GLfloat deltaTime);
	float m_fTimePassed;
	float m_velocity = 1.0f;
};


#pragma once
#include "GameObject/core/Object.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/utils/AABB.h"
//#include "utilities.h"
#include "../../Utilities/utilities.h"
#include <memory>

class Gun;
class Animation;
// an actor, spawns when gun is fired
// delete self when reaching max range
// add projectile hit creature
//		if self coord = creature coord -> call function isHit to creature holder obj of game state -> deduct hp (isHit int, > 3 = die())
class Projectile : public Object
{
public:
	std::weak_ptr<Gun> m_owner;
	std::shared_ptr<Animation> m_anim;

	int m_id;
	Vector2 m_startPos;
	Vector2 m_endPos;
	float m_moveSpeed = 50.0f;

	std::shared_ptr<AABB> m_hitbox;

	Projectile(std::weak_ptr<Gun> owner);
	void ProjLoop();
	void SetProjectile(Vector2 startPos, Vector2 endPos);
	void Update(GLfloat deltaTime);
	float m_fTimePassed;


	float m_velocity = 300.0f;
	Vector3 direction;
};


#pragma once
#include "../../Utilities/utilities.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/core/Object.h"
#include "GameObject/utils/AABB.h"
#include <memory>

class Gun;
class Animation;

// an actor, spawns when gun is fired
// delete self when reaching max range
class Projectile : public Object
{
public:
	std::shared_ptr<Gun> m_owner;
	std::shared_ptr<Animation> m_anim;

	int m_id;
	Vector2 m_startPos;
	Vector2 m_endPos;
	float m_moveSpeed = 50.0f;

	std::shared_ptr<AABB> m_hitbox;

	Projectile();
	void ProjLoop();
	void SetProjectile(Vector3 startPos, Vector3 endPos);
	void Update(GLfloat deltaTime);
	float m_fTimePassed;
	float m_velocity = 300.0f;
	Vector3 direction;
};
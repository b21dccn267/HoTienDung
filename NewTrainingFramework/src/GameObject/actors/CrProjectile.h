#pragma once
#include "GameObject/core/Object.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/utils/AABB.h"
#include <memory>

class CreatureGun;
class Animation;

class CrProjectile
{
public:
	std::shared_ptr<Animation> m_anim;

	bool m_isActive;
	Vector2 m_startPos;
	Vector2 m_endPos;
	float m_moveSpeed = 50.0f;

	std::shared_ptr<AABB> m_hitbox;

	CrProjectile();
	void ProjLoop();
	void SetProjectile(Vector3 startPos, Vector3 endPos);
	void Update(GLfloat deltaTime);
	float m_fTimePassed;
	float m_velocity = 300.0f;
	Vector3 direction;
};


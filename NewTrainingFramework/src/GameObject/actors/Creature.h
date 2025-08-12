#pragma once
#include "GameObject/core/Animation.h"
#include <memory>

class CreatureController;
class AABB;

class Creature 
{
protected:

	bool m_cooldownIsActive = false;
	float m_timeSinceSpawn = 0.0f;
public:
	std::shared_ptr<Animation> m_anim;
	std::shared_ptr<CreatureController> m_control;

	std::shared_ptr<AABB> m_hitbox;

	int health = 1;
	int damage = 1;

	Creature();
	virtual ~Creature();
	void Init();

	//animation functions
	virtual void Idle();
	virtual void Jump(); // unused, exists as a demo; if used, there should be jump anims for all directions
	virtual void LookUp();
	virtual void LookDown();
	virtual void LookTopRight();
	virtual void LookTopLeft();
	virtual void LookRight();
	virtual void LookLeft();
	virtual void LookBottomRight();
	virtual void LookBottomLeft();
	void Die();

	void Draw();
	void Update(GLfloat deltaTime);
	void Update2DPosition();
	void Move(float deltaTime, Vector2 heroPos);
};


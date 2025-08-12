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
	~Creature();
	void Init();

	//animation functions
	void Idle();
	void Jump(); // unused, exists as a demo; if used, there should be jump anims for all directions
	void LookUp();
	void LookDown();
	void LookTopRight();
	void LookTopLeft();
	void LookRight();
	void LookLeft();
	void LookBottomRight();
	void LookBottomLeft();
	void Die();

	void Draw();
	void Update(GLfloat deltaTime);
	void Update2DPosition();
	void Move(float deltaTime, Vector2 heroPos);
};


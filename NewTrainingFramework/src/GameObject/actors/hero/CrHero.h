#pragma once
#include "../Utilities/utilities.h"
#include "GameObject/actors/Creature.h"
#include "GameObject/core/Animation.h"
#include "GameObject/items/weapons/Sword.h"
#include <memory>

class AABB;

// class for hero2 without Creature class binds
class CrHero
{
public:
	std::shared_ptr<Animation> m_anim;
	std::shared_ptr<Sword> m_sword;
	std::shared_ptr<AABB> m_hitbox;

	int m_health;
	int m_attack;



	CrHero();
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
	//void FireGun();
};
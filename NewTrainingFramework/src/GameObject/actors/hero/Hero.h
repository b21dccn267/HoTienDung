#pragma once
#include <memory>
#include "../Utilities/utilities.h"
#include <GameObject/core/Animation.h>
#include <GameObject/items/weapons/Gun.h>

class AABB;
class Hero : public std::enable_shared_from_this<Hero>
{
public:
	std::shared_ptr<Animation> m_anim;
	std::shared_ptr<Gun> m_gun;

	//std::shared_ptr<Belongings> m_belongings;
	std::shared_ptr<AABB> m_hitbox;

	Hero();
	void Init();

	int health = 10; // should be buffed by armor stuff, which means for now theres no "armor" attribute
	int attack = 2;  


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
	void FireGun();

};


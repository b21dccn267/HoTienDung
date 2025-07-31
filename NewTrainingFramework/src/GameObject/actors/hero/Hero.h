#pragma once
#include "../../core/Animation.h"
#include "../../items/weapons/Gun.h"
#include "Belongings.h"
#include <memory>

class Hero
{
public:
	std::shared_ptr<Animation> m_anim;
	std::shared_ptr<Gun> m_gun;

	std::shared_ptr<Belongings> m_belongings;

	Hero();

	//animation functions
	void Idle();
	void Jump(); // unused, exists as a demo
	void LookUp();
	void LookTopRight();
	void LookRight();
	void LookBottomRight();
	void LookDown();
	void LookBottomLeft();
	void LookLeft();
	void LookTopLeft();

	void Draw();
	void Update(GLfloat deltaTime);
	void Update2DPosition();
	void FireGun();

};


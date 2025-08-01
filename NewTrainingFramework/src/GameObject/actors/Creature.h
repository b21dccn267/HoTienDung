#pragma once
#include "../core/Animation.h"
#include <memory>

class Creature
{
public:
	std::shared_ptr<Animation> m_anim;

	Creature();

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

	void Draw();
	void Update(GLfloat deltaTime);
	void Update2DPosition();
};


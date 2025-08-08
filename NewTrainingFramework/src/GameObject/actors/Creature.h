#pragma once
#include "GameObject/core/Animation.h"
#include <memory>

class CreatureController;

class Creature : public std::enable_shared_from_this<Creature>
{
public:
	std::shared_ptr<Animation> m_anim;
	std::shared_ptr<CreatureController> m_control;

	Creature();
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
};


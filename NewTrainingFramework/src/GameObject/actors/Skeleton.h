#pragma once
#include "Creature.h"

class CreatureController;

class Skeleton : public Creature
{
public:
	int m_id;
	bool m_isDie;

	Skeleton();

	void Jump() override; // unused, exists as a demo; if used, there should be jump anims for all directions
	void LookUp() override;
	void LookDown() override;
	void LookTopRight() override;
	void LookTopLeft() override;
	void LookRight() override;
	void LookLeft() override;
	void LookBottomRight() override;
	void LookBottomLeft() override;
	void Idle() override;
	void Die();
	void Move(float deltaTime, Vector2 heroPos) override;

	void Draw() override;
	void Update(float deltaTime) override;
};


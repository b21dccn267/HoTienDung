#pragma once
#include "Creature.h"

class CreatureController;

class AmogusGunner : public Creature
{
public:
	int m_id;
	bool m_isDie;

	AmogusGunner();

	void TestAllSprites();
	void Idle() override;
	void LookRight() override;
	void LookLeft() override;
	void LookDown() override;
	void ShootAnimRight();
	void ShootAnimLeft();
	void Die();

	
	void Move(float deltaTime, Vector2 heroPos) override;
};
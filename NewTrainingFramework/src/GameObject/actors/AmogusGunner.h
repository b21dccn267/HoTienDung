#pragma once
#include "Creature.h"

class CreatureController;

class AmogusGunner : public Creature
{
public:
	int m_id;
	bool m_isDie;

	AmogusGunner();

	void Idle() override;
	void LookRight() override;
	void LookLeft() override;
	void ShootAnimRight();
	void ShootAnimLeft();
	void Die();
	void TestAllSprites();
};
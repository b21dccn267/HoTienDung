#pragma once
#include "Creature.h"
#include <memory>


class CreatureController;
class CreatureGun;

class AmogusGunner : public Creature, public std::enable_shared_from_this<AmogusGunner>
{
public:
	int m_id;
	bool m_isDie;

	std::shared_ptr<CreatureGun> m_crGun;

	AmogusGunner();

	void TestAllSprites();
	

	void LookRight() override;
	void LookLeft() override;
	//void LookDown() override;
	void ShootAnimRight();
	void ShootAnimLeft();
	void Idle() override;
	void Die();


	
	void Move(float deltaTime, Vector2 heroPos) override;

private: // ensures unused functions cannot be called
	void Jump() override {};
	void LookUp() override {};
	void LookDown() override {};
	void LookTopRight() override {};
	void LookTopLeft() override {};
	void LookBottomRight() override {};
	void LookBottomLeft() override {};
};
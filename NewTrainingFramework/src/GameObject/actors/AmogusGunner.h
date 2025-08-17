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

	bool m_isOnCooldown;
	bool m_canMove;


	std::shared_ptr<CreatureGun> m_crGun;

	AmogusGunner();
	void Init();
	std::shared_ptr<AmogusGunner> getPtr() {
		return shared_from_this();
	}

	void LookRight() override;
	void LookLeft() override;
	void ShootAnimRight();
	void ShootAnimLeft();
	void Idle() override;
	void Die();
	void Move(float deltaTime, Vector2 heroPos) override;
	void Draw();
	void Update(float deltaTime);

private: // ensures unused functions cannot be called
	void Jump() override {};
	void LookUp() override {};
	void LookDown() override {};
	void LookTopRight() override {};
	void LookTopLeft() override {};
	void LookBottomRight() override {};
	void LookBottomLeft() override {};
};
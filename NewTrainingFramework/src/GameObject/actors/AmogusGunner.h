#pragma once
#include "Creature.h"
#include <memory>


class CreatureController;
class CreatureGun;

class AmogusGunner : public Creature
{
public:
	int m_id;

	bool m_isOnCooldown;
	float m_cooldownTimer;
	float m_cooldown;
	bool m_canMove;


	std::shared_ptr<CreatureGun> m_crGun;

	AmogusGunner();
	void Init();

	void LookRight() override;
	void LookLeft() override;
	void ShootAnimRight();
	void ShootAnimLeft();
	void Idle() override;
	void Die();
	void Move(float deltaTime, Vector2 heroPos) override;
	void Draw() override;
	void Update(float deltaTime) override;

	bool DoDerived(std::shared_ptr<AABB> hitbox) override;

private: // ensures unused functions cannot be called
	void Jump() override {};
	void LookUp() override {};
	void LookDown() override {};
	void LookTopRight() override {};
	void LookTopLeft() override {};
	void LookBottomRight() override {};
	void LookBottomLeft() override {};
};
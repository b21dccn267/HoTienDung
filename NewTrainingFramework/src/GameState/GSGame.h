#pragma once
#include "GameStateBase.h"
#include "GameObject/core/Object.h"
#include "GameObject/core/Animation.h"
#include "GameManager/SoundManager.h"
#include "GameObject/actors/hero/Hero.h"
#include "GameObject/actors/Creature.h"
#include "GameObject/actors/CreatureSpawner.h"
#include "GameObject/actors/Projectile.h"
#include "GameObject/ui/HealthBar.h"
#include <memory>
#include <vector>


class GSGame : public GameStateBase
{
public:
	//std::shared_ptr<Animation> m_gsGameObject;
	std::shared_ptr<Hero> m_hero;
	std::shared_ptr<Creature> m_hero2;
	std::shared_ptr<CreatureSpawner> m_creatureSpawner;
	std::shared_ptr<HealthBar> m_healthBar1;
	std::shared_ptr<HealthBar> m_healthBar2;

	GSGame() : GameStateBase(StateType::STATE_MENU) {}
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;

	~GSGame() override;
};


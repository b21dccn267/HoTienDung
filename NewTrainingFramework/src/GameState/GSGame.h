#pragma once
#include "GameStateBase.h"
#include "../GameObject/core/Object.h"
#include "../GameObject/core/Animation.h"
#include "../GameManager/SoundManager.h"
#include "../GameObject/actors/hero/Hero.h"
#include "../GameObject/actors/Creature.h"
#include "../GameObject/actors/Projectile.h"
#include <memory>
#include <vector>


class GSGame : public GameStateBase
{
public:
	//std::shared_ptr<Animation> m_gsGameObject;
	std::shared_ptr<Hero> m_hero;
	std::shared_ptr<Creature> m_creature;

	// test
	std::shared_ptr<Projectile> m_proj;
	// gun is in m_hero
	// if mouseclick, gun fires
	// when gun fires, gun create a projectile (projectileManager might be here)
	// projectile will fly to a direction, and then die (kill by dist, or by time passed)
	//
	// hierachy:
	// gsGame owns hero, does mouse event
	// hero owns gun, call fire()
	// gun defines fire(), spawns projectile
	// projectile manages its own lifecycle based on input
	//
	// proj needs deltatime from update

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


#pragma once
#include "GameStateBase.h"
#include "Object.h"
#include <memory>

// this class should load a 2d asset
// by having an Object class member
class GSIntro : public GameStateBase
{
public:
	std::shared_ptr<Object> m_object;

	//using GameStateBase::GameStateBase;
	GSIntro() : GameStateBase(StateType::STATE_INTRO) {}
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(bool bIsPressed) override;
	void HandleMouseEvent() override;
	void Cleanup() override;

	~GSIntro() override;
};


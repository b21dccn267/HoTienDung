#pragma once
#include "GameStateBase.h"
#include "StateType.h"
#include "Object.h"
#include <memory>

// this class should load a 2d asset
// by having an Object class member
class GSIntro : public GameStateBase
{
public:
	std::shared_ptr<Object> m_object;

	using GameStateBase::GameStateBase;
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	virtual void CreateState() override;
	virtual void Draw() override;
	virtual void Update(float deltaTime) override;
	virtual void HandleKeyEvent() override;
	virtual void HandleMouseEvent() override;
	virtual void Cleanup() override;

	~GSIntro() override;
};


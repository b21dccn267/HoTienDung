#pragma once
#include <memory>
#include "Object.h"
#include "GameStateBase.h"


class GSMenu : public GameStateBase
{
public:
	std::shared_ptr<Object> m_object;

	//using GameStateBase::GameStateBase;
	GSMenu() : GameStateBase(StateType::STATE_MENU) {}
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(bool bIsPressed) override;
	void HandleMouseEvent() override;
	void Cleanup() override;

	~GSMenu() override;
};


#pragma once
#include "GameStateBase.h"
#include "Object.h"
#include <memory>

class GSPlay : public GameStateBase
{
public:
	std::shared_ptr<Object> m_object;

	//using GameStateBase::GameStateBase;
	GSPlay() : GameStateBase(StateType::STATE_MENU) {}
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;

	~GSPlay() override;
};


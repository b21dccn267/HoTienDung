#pragma once
#include "GameStateBase.h"
#include "Object.h"
#include <memory>

class GSPlay : public GameStateBase
{
public:
	std::shared_ptr<Object> m_object;

	using GameStateBase::GameStateBase;
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	virtual void CreateState() override;
	virtual void Update() override;
	virtual void HandleKeyEvent() override;
	virtual void HandleMouseEvent() override;
	virtual void Cleanup() override;

	~GSPlay() override;
};


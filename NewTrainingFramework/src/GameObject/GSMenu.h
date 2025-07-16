#pragma once
#include "GameStateBase.h"


class GSMenu : public GameStateBase
{
public:


	GSMenu(int id = 1);
	void Pause() override;
	void Exit() override;
	void Resume() override;
	//GameStateBase CreateState() override;
	virtual void CreateState() override;
	virtual void Update() override;
	virtual void HandleKeyEvent() override;
	virtual void HandleMouseEvent() override;
	virtual void Cleanup() override;

	~GSMenu() override;
};


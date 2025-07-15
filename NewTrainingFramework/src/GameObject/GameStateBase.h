#pragma once


class GameStateBase
{
public:
	GameStateBase();
	virtual void Pause() = 0;
	virtual void Exit() = 0;
	virtual void Resume() = 0;
	//virtual GameStateBase CreateState() = 0;
	virtual void CreateState() = 0;
	virtual ~GameStateBase() = 0;
};


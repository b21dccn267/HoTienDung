#pragma once
#include "GameStateBase.h"
#include <vector>
#include <memory>


// this class manages game states
class GameStateMachine
{
public:
	GameStateMachine(const GameStateMachine& instance) = delete;
	static GameStateMachine* instance;
	static GameStateMachine* GetInstance()
	{
		if (!instance) {
			instance = new GameStateMachine();
		}
		return instance;
	}

	std::vector<std::unique_ptr<GameStateBase>> m_stack;

	int m_pActiveState;
	int m_pNextState;
	int m_StateStack;

	
	void PushState(std::unique_ptr<GameStateBase> state);
	//void PushState();
	void PopState();
	void PerformStateChange();
	void CurrentState();
private:
	GameStateMachine();
};


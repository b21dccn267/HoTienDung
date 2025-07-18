#pragma once
#include "GameStateBase.h"
#include <vector>
#include <memory>
#include <stack>


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

	std::stack<std::unique_ptr<GameStateBase>> m_stack;

	std::unique_ptr<GameStateBase> m_pActiveState;
	std::unique_ptr<GameStateBase> m_pNextState;

	
	void PushState(StateType state);
	void PopState();
	void PerformStateChange(std::unique_ptr<GameStateBase> state);
private:
	GameStateMachine();
};


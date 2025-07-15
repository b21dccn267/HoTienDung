#include "stdafx.h"
#include "GameStateMachine.h"

GameStateMachine* GameStateMachine::instance = nullptr;

// game state loop
// pop old, push new, call stateChange()
GameStateMachine::GameStateMachine()
{
}

void GameStateMachine::PushState(std::unique_ptr<GameStateBase> state)
{
	m_stack.emplace_back(std::move(state));
}

void GameStateMachine::PopState()
{
	m_stack.pop_back();
}

void GameStateMachine::PerformStateChange()
{

}

void GameStateMachine::CurrentState()
{
}

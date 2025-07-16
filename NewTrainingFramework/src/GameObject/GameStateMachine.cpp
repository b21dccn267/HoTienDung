#include "stdafx.h"
#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine* GameStateMachine::instance = nullptr;

// game state loop
// pop old, push new, call stateChange()
GameStateMachine::GameStateMachine()
{
}

void GameStateMachine::PushState(std::unique_ptr<GameStateBase> state)
{
	m_pActiveState = state->m_stateId;
	m_stack.emplace_back(std::move(state));	
}

void GameStateMachine::PopState()
{
	if (m_stack.empty()) {
		return;
	}
	m_stack.back()->Exit();
	m_stack.pop_back();
	if (!m_stack.empty()) {
		m_stack.back()->Resume(); //assume init
	}
}

void GameStateMachine::PerformStateChange(std::unique_ptr<GameStateBase> state)
{
	PopState();
	PushState(std::move(state));
}

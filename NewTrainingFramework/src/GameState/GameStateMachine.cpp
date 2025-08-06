#include "GameStateMachine.h"
#include "GameStateBase.h"


GameStateMachine* GameStateMachine::instance = nullptr;

void GameStateMachine::PushState(StateType state)
{
	m_pNextState = GameStateBase::CreateState(state);

	//Pause laij active 
	m_pNextState->Init();
	if (!m_stack.empty()) {
		//m_stack.top()->Pause();
	}
	m_stack.push(m_pNextState);


}
void GameStateMachine::PopState()
{
	if (m_stack.empty()) {
		return;
	}
	m_stack.top()->Exit();
	m_stack.pop();
	if (!m_stack.empty()) {
		m_stack.top()->Resume();
	}
}

void GameStateMachine::PerformStateChange(StateType state)
{
///
}

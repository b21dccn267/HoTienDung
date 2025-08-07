#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine* GameStateMachine::instance = nullptr;

void GameStateMachine::PushState(StateType state)
{
    m_pNextState = GameStateBase::CreateState(state);

    // Gọi Pause() cho trạng thái hiện tại (nếu có)
    if (!m_stack.empty()) {
        m_stack.top()->Pause();
    }

    // Khởi tạo trạng thái mới và đẩy vào stack
    m_pNextState->Init();
    m_stack.push(m_pNextState);
}

void GameStateMachine::PopState()
{
    if (m_stack.empty()) {
        return;
    }

    // Thoát trạng thái hiện tại
    m_stack.top()->Exit();
    m_stack.pop();

    // Gọi Resume() cho trạng thái trước đó (nếu có)
    if (!m_stack.empty()) {
        m_stack.top()->Resume();
    }
}

void GameStateMachine::PerformStateChange(StateType state)
{
    // Chưa được triển khai, để lại như hiện tại
}
#pragma once
#include "GameButton.h"
#include "GameManager/SoundManager.h"
#include "GameObject/core/Animation.h"
#include "GameObject/core/Object.h"
#include "GameObject/actors/Creature.h"
#include "GameStateBase.h"
#include <memory>
#include <vector>

class GSPlay : public GameStateBase
{
public:
    std::vector<std::shared_ptr<Object>> m_gsPlayObjects;
    std::vector<std::shared_ptr<GameButton>> m_gsPlayButtons;
    std::shared_ptr<Creature> m_creature; // Đối tượng Creature riêng biệt
    bool m_isPaused; // Biến kiểm soát trạng thái tạm dừng

    GSPlay() : GameStateBase(StateType::STATE_PLAY), m_isPaused(false) {}
    void Init() override;
    void Pause() override;
    void Exit() override;
    void Resume() override;
    void Draw() override;
    void Update(float deltaTime) override;
    void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
    void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
    void Cleanup() override;

    ~GSPlay() override;

private:
    static void OnPauseButtonClick();
};
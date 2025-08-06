#pragma once
#include "GameButton.h"
#include "GameObject/core/Object.h"
#include "GameStateBase.h"
#include <memory>
#include <vector>


class GSMenu : public GameStateBase
{
public:
	std::vector<std::shared_ptr<Object>> m_gsMenuObjects;
	std::vector<std::shared_ptr<GameButton>> m_gsMenuGameButtons;

	GSMenu() : GameStateBase(StateType::STATE_MENU) {}
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;

	~GSMenu() override;
};


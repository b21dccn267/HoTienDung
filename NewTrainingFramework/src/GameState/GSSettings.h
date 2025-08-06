#pragma once
#include "GameButton.h"
#include "GameObject/core/Object.h"
#include "GameStateBase.h"
#include <memory>
#include <vector>

class GSSettings : public GameStateBase
{
public:
	std::vector<std::shared_ptr<Object>> m_gsSettingsObjects;
	std::vector<std::shared_ptr<GameButton>> m_gsSettingsGameButtons;

	GSSettings() : GameStateBase(StateType::STATE_SETTINGS) {}
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;

	~GSSettings() override;
};
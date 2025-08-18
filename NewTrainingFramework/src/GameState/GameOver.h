#pragma once
#include "GameButton.h"
#include "GameObject/core/Object.h"
#include "GameStateBase.h"
#include <memory>
#include <vector>
#include <string>

class GameOver : public GameStateBase
{
public:
	std::vector<std::shared_ptr<Object>> m_gameOverObjects;
	std::vector<std::shared_ptr<GameButton>> m_gameOverButtons;
	static std::string s_pendingCustomText;

	GameOver() : GameStateBase(StateType::STATE_GAMEOVER) {}
	GameOver(const std::string& customText) : GameStateBase(StateType::STATE_GAMEOVER), m_customText(customText) {}
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;

	~GameOver() override;

private:
	std::string m_customText; 

	// Callback functions for buttons
	static void OnRestartButtonClick();
	static void OnMainMenuButtonClick();
};
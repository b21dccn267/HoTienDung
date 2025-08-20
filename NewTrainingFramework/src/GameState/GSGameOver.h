#pragma once
#include "GameButton.h"
#include "GameObject/core/Object.h"
#include "GameStateBase.h"
#include <memory>
#include <vector>
#include <string>

class GSGameOver : public GameStateBase
{
public:
	std::vector<std::shared_ptr<Object>> m_gameOverObjects;
	std::vector<std::shared_ptr<GameButton>> m_gameOverButtons;

	// Static members for setting text from other states
	static std::string s_pendingMainText;
	static std::string s_pendingSubText;

	GSGameOver() : GameStateBase(StateType::STATE_GAMEOVER) {}
	GSGameOver(const std::string& mainText, const std::string& subText = "") :
		GameStateBase(StateType::STATE_GAMEOVER), m_mainText(mainText), m_subText(subText) {
	}

	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;

	~GSGameOver() override;

	// Helper methods to set text
	void SetMainText(const std::string& text) { m_mainText = text; }
	void SetSubText(const std::string& text) { m_subText = text; }
	static void SetPendingText(const std::string& mainText, const std::string& subText = "");

private:
	std::string m_mainText = "GAME OVER";  // Default main text
	std::string m_subText = "";            // Optional subtitle

	// Callback functions for buttons
	static void OnRestartButtonClick();
	static void OnMainMenuButtonClick();
};
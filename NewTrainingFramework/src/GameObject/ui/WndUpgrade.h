#pragma once
#include <memory>
#include "../../Utilities/utilities.h"


class Object;
class GameButton;
class Vector2;
class Hero;

class WndUpgrade
{
public:
	std::shared_ptr<Object> m_upgradeFrame;
	std::shared_ptr<GameButton> m_upgradeButton1;
	std::shared_ptr<GameButton> m_upgradeButton2;
	std::shared_ptr<GameButton> m_upgradeButton3;

	bool m_isActive;

	WndUpgrade();
	void Draw();
	void Update(GLint x, GLint y, bool isPressed);
};
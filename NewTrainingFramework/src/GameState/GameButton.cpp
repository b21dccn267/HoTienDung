#include "stdafx.h"
#include "GameButton.h"


GameButton::GameButton(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader)
	: Object(model, texture, shader), m_pBtnClick(nullptr), m_isHolding(false)
{
}

GameButton::~GameButton()
{
}

void GameButton::SetOnClick(void(*pBtnClickFun)())
{
	m_pBtnClick = pBtnClickFun;
}

bool GameButton::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	bool isHandled = false;
	if (!bIsPressed)
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2))
		{
			m_isHolding = true;
		}
	}
	else
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2)
			&& m_isHolding == true)
		{
			m_pBtnClick();
			isHandled = true;
		}
		m_isHolding = false;
	}
	return isHandled;
}

bool GameButton::IsHolding()
{
	return m_isHolding;
}



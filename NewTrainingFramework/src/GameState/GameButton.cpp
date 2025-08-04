#include "GameButton.h"
#include "../GameObject/core/Model.h"
#include "../GameObject/core/Texture.h"
#include "../GameObject/core/Shaders.h"
#include "../GameObject/core/Object.h"

GameButton::GameButton(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader)
    : Object(model, texture, shader), m_pBtnClick(nullptr), m_isHolding(false),
    m_normalTexture(texture), m_pressedTexture(nullptr)
{
}

GameButton::GameButton(std::shared_ptr<Model> model, std::shared_ptr<Texture> normalTexture,
    std::shared_ptr<Texture> pressedTexture, std::shared_ptr<Shaders> shader)
    : Object(model, normalTexture, shader), m_pBtnClick(nullptr), m_isHolding(false),
    m_normalTexture(normalTexture), m_pressedTexture(pressedTexture)
{
}

GameButton::~GameButton()
{
}

// allows lambda binding
void GameButton::SetOnClick(void(*pBtnClickFun)())
{
    m_pBtnClick = pBtnClickFun;
}

void GameButton::SetNormalTexture(std::shared_ptr<Texture> texture)
{
    m_normalTexture = texture;
    if (!m_isHolding) {
        m_pTexture = texture; // Sử dụng m_pTexture của Object class
    }
}

void GameButton::SetPressedTexture(std::shared_ptr<Texture> texture)
{
    m_pressedTexture = texture;
}

bool GameButton::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
    bool isHandled = false;
    if (bIsPressed)
    {
        if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
            && (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2))
        {
            m_isHolding = true;
            // Chuyển sang texture pressed nếu có
            if (m_pressedTexture) {
                m_pTexture = m_pressedTexture; // Sử dụng m_pTexture của Object class
            }
        }
    }
    else
    {
        if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
            && (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2)
            && m_isHolding == true)
        {
            if (m_pBtnClick) {
                m_pBtnClick();
            }
            isHandled = true;
        }

        // Reset về texture normal khi thả chuột
        m_isHolding = false;
        if (m_normalTexture) {
            m_pTexture = m_normalTexture; // Sử dụng m_pTexture của Object class
        }
    }
    return isHandled;
}

bool GameButton::IsHolding()
{
    return m_isHolding;
}
#pragma once
#include "GameObject/core/Object.h"
#include <memory>
#include <functional>

class GameButton : public Object
{
public:
    GameButton() : Object(), m_pBtnClick(nullptr), m_isHolding(false),
        m_normalTexture(nullptr), m_pressedTexture(nullptr) {
    };
    GameButton(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader);
    GameButton(std::shared_ptr<Model> model, std::shared_ptr<Texture> normalTexture,
        std::shared_ptr<Texture> pressedTexture, std::shared_ptr<Shaders> shader);
    ~GameButton();

    void SetOnClick(std::function<void()> btnClickFun);
    bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
    bool IsHolding();

    // Setter cho textures
    void SetNormalTexture(std::shared_ptr<Texture> texture);
    void SetPressedTexture(std::shared_ptr<Texture> texture);

private:
    std::function<void()> m_pBtnClick; 
    bool m_isHolding;
    std::shared_ptr<Texture> m_normalTexture;
    std::shared_ptr<Texture> m_pressedTexture;
};
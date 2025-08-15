#include "Timer.h"
#include "GameObject/core/Object.h"
#include "GameObject/core/TextRenderer.h"
#include "GameManager/ResourceManager.h"
#include <string>

Timer::Timer()
{
	m_time = 60;
	m_updateCount = 0.0f;

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = std::make_shared<Texture>(TextRenderer::RenderText(std::to_string(m_time).c_str()));
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	m_displayText = std::make_shared<Object>(model, texture, shader);
	m_displayText->Set2DPosition(Vector2(450, 50));
	m_displayText->SetSize(100, 100);
}

void Timer::StartTimer(int startTime)
{
	m_time = startTime;
	m_isActive = true;
}

void Timer::PauseTimer()
{
	m_isActive = false;
}

void Timer::ResumeTimer()
{
	m_isActive = true;
}

void Timer::UpdateTimer(float deltaTime)
{
	if (m_time != 0 && m_isActive == true) {
		m_updateCount += deltaTime;
		if (m_updateCount >= 1.0f) {
			m_time--;
			std::string s = std::to_string(m_time);
			m_displayText->m_pTexture = std::make_shared<Texture>(TextRenderer::RenderText(s.c_str()));
			m_updateCount = 0.0f;
		}
	}
}

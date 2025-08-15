#include "HealthBar.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/actors/hero/Hero.h"
#include "../../Utilities/utilities.h"


HealthBar::HealthBar(float barPosX, float barPosY)
{
	m_barPosX = barPosX;
	m_barPosY = barPosY;

	//default value of barposx and y would be 500
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(38);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	m_healthBarFrame = std::make_shared<Object>(model, texture, shader);
	m_healthBarFrame->Set2DPosition(Vector2(m_barPosX, m_barPosY));
	m_healthBarFrame->SetSize(400, 80); // 400, 80
	texture = ResourceManager::GetInstance()->GetTexture(39);
	m_healthBarFill = std::make_shared<Object>(model, texture, shader);
	m_healthBarFill->Set2DPosition(Vector2(barPosX - 161.0f, barPosY));
	m_healthBarFill->SetSize(320*2, 40); // 300, 40
}

void HealthBar::Draw()
{
	m_healthBarFrame->Draw();
	m_healthBarFill->Draw();
}

void HealthBar::UpdateHealth(int heroHealth)
{
	m_currHealth = heroHealth;

	if (m_currHealth) {
		m_healthBarFill->SetSize(644 * ((float)m_currHealth / m_health), 40);
	}
}
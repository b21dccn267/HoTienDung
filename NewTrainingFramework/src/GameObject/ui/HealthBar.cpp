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
	m_healthBarFill->Set2DPosition(Vector2(barPosX, barPosY));
	m_healthBarFill->SetSize(300, 40); // 300, 40
}

void HealthBar::Draw()
{
	m_healthBarFrame->Draw();
	m_healthBarFill->Draw();
}

void HealthBar::UpdateHealth(int heroHealth)
{
	m_currHealth = heroHealth;
	// freeze this when hp reach 0 so it wont get 'flipped'
	if (m_currHealth) {
		m_healthBarFill->SetSize(300 * ((float)m_currHealth / m_health), 40);
		m_healthBarFill->Set2DPosition(Vector2(m_barPosX * ((float)m_currHealth / m_health), m_barPosY));
	}
}
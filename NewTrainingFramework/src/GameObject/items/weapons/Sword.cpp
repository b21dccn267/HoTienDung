#include "Sword.h"
#include <memory>
#include "GameManager/ResourceManager.h"


Sword::Sword()
{
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(30);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	m_self = std::make_shared<Object>(model, texture, shader);
	m_self->Set2DPosition(0, 0); // bind to hero pos later
	m_self->SetSize(100, 100);
}

void Sword::UseSword()
{
	m_isActive = true;
}

// hero will call this in its draw()
void Sword::Draw()
{
	if (m_isActive) {
		m_self->Draw(); 
	}
}

void Sword::Update(float deltaTime)
{
	
}

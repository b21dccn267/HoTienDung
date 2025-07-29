#include "stdafx.h"
#include "Projectile.h"
#include "Globals.h"
#include "../../GameManager/ResourceManager.h"


Projectile::Projectile()
{
	this->m_pModel = ResourceManager::GetInstance()->GetModel(0);
	this->m_pTexture = ResourceManager::GetInstance()->GetTexture(6);
	this->m_pShader = ResourceManager::GetInstance()->GetShader(0);
	this->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	this->SetSize(100, 100);
}

void Projectile::Destroy()
{

}

//void Projectile::Fire()
//{
//	if (m_isFired == true) {
//		return;
//	}
//	m_isFired = true;
//}

void Projectile::Update(GLfloat deltaTime)
{
	printf("flying...\n");
	m_fTimePassed += deltaTime;
	if (m_fTimePassed >= 2.0f) {
		//Destroy();
		//~Projectile::Projectile();
		m_position.x = 0.0f;
		m_position.y = 0.0f;
		printf("stopped\n");
		return;
	}
	m_position.x += 5.0f;
}
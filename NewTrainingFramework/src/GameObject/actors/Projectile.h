#pragma once
#include "../core/Object.h"
#include "../../GameManager/ResourceManager.h"
#include <memory>


// an actor, spawns when gun is fired
// delete self when reaching max range
class Projectile : public Object
{
public:
	//Projectile() : 
	//	Object(
	//		ResourceManager::GetInstance()->GetModel(0),
	//		ResourceManager::GetInstance()->GetTexture(6),
	//		ResourceManager::GetInstance()->GetShader(0)
	//		),
	//	m_fTimePassed(0.0f) {};
	Projectile();
	~Projectile() {};
	void Destroy();
	//void Fire(); //is in gun
	void Update(GLfloat deltaTime);
	float m_fTimePassed;
	//bool m_isActive;
};


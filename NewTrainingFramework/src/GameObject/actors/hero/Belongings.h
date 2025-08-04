#pragma once
#include "../../items/weapons/Gun.h"

// master class for Hero 
// contains all items for Hero to interact
// functions include item management, as well as delegate functions
class Belongings
{
	//std::shared_ptr<Gun> m_gun;

	void SetToActive();		// set a weapon in possession of hero as active (can only fire 1 weapon for now)
	void UseActiveWeapon();
};


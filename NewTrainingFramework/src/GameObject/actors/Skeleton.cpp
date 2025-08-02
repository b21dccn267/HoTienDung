#include "Skeleton.h"
#include "../../GameManager/ResourceManager.h"
#include <vector>

Skeleton::Skeleton()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

// effects couldbe been put into a potential EffectsManager instance in game state
// no need rn, as enemy death explosion removes its prev model before loading
void Skeleton::Die()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(7);
	//m_anim->
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3, 4, 5});
}

// also add Knockback upon bullet contact
#include "Skeleton.h"
#include "../../GameManager/ResourceManager.h"

Skeleton::Skeleton()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

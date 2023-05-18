#include "pch.h"
#include "Powerup.h"
#include "Collider.h"
#include "PlayerComponent.h"

void D2D::Powerup::OnTriggerEnter(const Collider* pCollider)
{
	if (auto player = pCollider->GetComponent<PlayerComponent>())
	{
		player->PowerupCollected(m_Type);
		GetOwner()->Destroy();
	}

}

#include "pch.h"
#include "Powerup.h"
#include "Collider.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"

void D2D::Powerup::OnTriggerEnter(const Collider* pCollider)
{
	if (auto player = pCollider->GetComponent<PlayerComponent>())
	{
		player->PowerupCollected(m_Type);

		ServiceLocator::GetSoundSystem().Play(3, 128);

		GetOwner()->Destroy();
	}

}

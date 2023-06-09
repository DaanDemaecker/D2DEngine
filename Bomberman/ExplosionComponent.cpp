#include "pch.h"
#include "ExplosionComponent.h"
#include "WorldEvents.h"

void D2D::ExplosionComponent::Destroy()
{
	ExplosionOverEvent explosionOverEvent{};
	explosionOverEvent.gridIndex = m_GridIndex;
	NotifyObservers(explosionOverEvent);
}

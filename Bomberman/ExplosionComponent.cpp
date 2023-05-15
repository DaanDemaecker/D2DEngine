#include "pch.h"
#include "ExplosionComponent.h"
#include "WorldEvents.h"

D2D::ExplosionComponent::~ExplosionComponent()
{
	ExplosionOverEvent explosionOverEvent{};
	explosionOverEvent.gridIndex = m_GridIndex;
	NotifyObservers(explosionOverEvent);
}

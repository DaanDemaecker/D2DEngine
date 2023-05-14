#pragma once
#include "Component.h"
#include "Subject.h"

namespace D2D
{
	class Collider : public Component, public Subject
	{
	public:
		Collider() = default;
		virtual ~Collider() = default;

		virtual void AddToPhysicsManager(bool isTrigger = false) = 0;

		virtual void TriggerOverlap(Collider* other) = 0;
	};
}

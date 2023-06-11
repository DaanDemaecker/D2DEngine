#pragma once
#include "Component.h"
#include "Subject.h"

namespace D2D
{
	class Collider : public Component
	{
	public:
		Collider() = default;
		virtual ~Collider() = default;

		virtual void AddToPhysicsManager(bool isTrigger = false) = 0;

		bool TriggerContainsCollider(const Collider* pCollider);
		void AddCollider(Collider* pCollider);
		void RemoveCollider(const Collider* pCollider);

		std::vector<Collider*>& GetCollidersInTrigger() { return m_pCollidersInTrigger; }

		bool IsTrigger() const { return m_IsTrigger; }
	private:
		std::vector<Collider*> m_pCollidersInTrigger{};
	protected:
		bool m_IsTrigger{ false };
	};
}

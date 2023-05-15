#pragma once
#include "Collider.h"
#include "Structs.h"

namespace D2D
{
	class Transform;

	class BoxCollider final : public Collider
	{
	public:
		BoxCollider();
		virtual ~BoxCollider();

		virtual void AddToPhysicsManager(bool isTrigger = false) override;

		void SetVariables(float width, float height, float offsetX = 0, float offsetY = 0);

		virtual void Render() const override;

		BoxColliderBounds& GetBounds();

	private:
		bool m_IsTrigger{ false };

		BoxColliderBounds m_Bounds{};

		Transform* m_pTransform{};
	};
}


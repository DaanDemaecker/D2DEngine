#pragma once
#include "Collider.h"
#include "Structs.h"

namespace D2D
{
	class Transform;

	class CapsuleCollider final : public Collider
	{
	public:
		CapsuleCollider();
		virtual ~CapsuleCollider();

		virtual void AddToPhysicsManager(bool isTrigger = false) override;

		void SetVariables(float height, float radius, float offsetX = 0, float offsetY = 0);

		virtual void LateUpdate() override;

		virtual void Render() const override;

		Capsule& GetBounds();

	private:
		Capsule m_Bounds{};

		Transform* m_pTransform{};
	};
}

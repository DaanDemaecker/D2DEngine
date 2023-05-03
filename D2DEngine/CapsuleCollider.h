#pragma once
#include "Component.h"
#include "Structs.h"

namespace D2D
{
	class Transform;

	class CapsuleCollider final : public Component
	{
	public:
		CapsuleCollider();
		~CapsuleCollider();

		void SetVariables(float height, float radius, float offsetX = 0, float offsetY = 0);

		virtual void LateUpdate() override;

		virtual void Render() const override;

		Capsule& GetBounds();

	private:
		Capsule m_Bounds{};

		Transform* m_pTransform{};
	};
}

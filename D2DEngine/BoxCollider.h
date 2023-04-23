#pragma once
#include "Component.h"
#include "Structs.h"

namespace D2D
{
	class Transform;

	class BoxCollider final : public Component
	{
	public:
		BoxCollider();
		~BoxCollider();

		void SetVariables(float width, float height, float offsetX = 0, float offsetY = 0);


		virtual void Update() override;

		virtual void Render() const override;

		BoxColliderBounds GetBounds();

	private:
		BoxColliderBounds m_Bounds{};

		Transform* m_pTransform{};
	};
}


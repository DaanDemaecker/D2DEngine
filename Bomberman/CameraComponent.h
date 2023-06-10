#pragma once
#include "Component.h"

namespace D2D
{
	class Transform;

	class CameraComponent final : public Component
	{
	public:
		CameraComponent();
		virtual ~CameraComponent() override = default;

		void SetPlayer(Transform* playerTransform, Transform* player2Transform = nullptr);

		void SetLevelBounds(float min, float max);

		virtual void LateUpdate() override;

	private:
		int m_WindowWidth{};
		int m_WindowHeight{};

		float m_CameraMin{};
		float m_CameraMax{};

		std::vector<Transform*> m_pPlayerTransforms{};

		Transform* m_pTransform{};
	};
}
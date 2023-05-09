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

		void SetPlayer(Transform* playerTransform);

		void SetLevelBounds(float min, float max);

		virtual void Update() override;

	private:
		int m_WindowWidth{};
		int m_WindowHeight{};

		float m_CameraMin{};
		float m_CameraMax{};

		Transform* m_pTransform{};
		Transform* m_pPlayerTransform{};
	};
}
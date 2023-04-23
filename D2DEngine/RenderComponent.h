#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace D2D
{
	class Transform;

	class RenderComponent final : public Component
	{
	public:
		RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void SetTexture(std::shared_ptr<Texture2D> pTexture);

		void SetOffset(float offsetX, float offSetY);

		virtual void Render() const override;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};

		float m_OffsetX{};
		float m_Offsety{};
	};
}


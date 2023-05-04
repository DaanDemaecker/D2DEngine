#pragma once
#include "Component.h"
#include "Texture2D.h"
#include "Structs.h"

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
		void SetSourceRect(const Rect& srcRect);

		void SetOffset(float offsetX, float offSetY);

		void SetDestRectBounds(float width, float height);

		virtual void Render() const override;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};

		float m_OffsetX{};
		float m_OffsetY{};

		float m_DestRectWidth{};
		float m_DestRectHeight{};

		Rect m_SrcRect{};
	};
}


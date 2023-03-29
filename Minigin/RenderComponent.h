#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace dae
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

		virtual void Render() const override;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}


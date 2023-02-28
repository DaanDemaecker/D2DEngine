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

		void SetTexture(std::shared_ptr<Texture2D> pTexture);

		void Render() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}


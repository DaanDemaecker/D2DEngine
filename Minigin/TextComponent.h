#pragma once
#include <string>
#include "Component.h"
#include <SDL_ttf.h>

namespace dae
{
	class Font;
	class RenderComponent;

	class TextComponent final : public Component
	{
	public:
		TextComponent() = default;
		virtual ~TextComponent() = default;

		virtual void Update() override;

		const std::string& GetText() const { return m_Text; }
		const SDL_Color& GetColor() const { return m_Color; }

		void SetFont(std::shared_ptr<Font> pFont);
		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		void SetColor(float r, float g, float b, float a = 255.f);

	private:

		bool m_NeedsUpdate{ false };
		std::string m_Text{" "};
		std::shared_ptr<Font> m_pFont;

		SDL_Color m_Color{ 255, 255, 255 };

		std::weak_ptr<RenderComponent> m_pRenderComponent;
	};
}

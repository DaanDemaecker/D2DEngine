#include <stdexcept>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "RenderComponent.h"

#include <iostream>

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		if (!m_pFont)
			return;

		if (m_pRenderComponent.expired())
		{
			m_pRenderComponent = GetComponent<RenderComponent>();

			if (m_pRenderComponent.expired())
				return;
		}

		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		m_pRenderComponent.lock()->SetTexture(std::make_shared<Texture2D>(texture));

		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> pFont)
{
	m_pFont = pFont;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(float r, float g, float b, float a)
{
	SetColor(SDL_Color{
		static_cast<unsigned char>(r),
		static_cast<unsigned char>(g),
		static_cast<unsigned char>(b),
		static_cast<unsigned char>(a),
		});
}

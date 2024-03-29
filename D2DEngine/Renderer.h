#pragma once
#include <SDL.h>
#include <memory>
#include "Singleton.h"

namespace D2D
{
	class Texture2D;
	struct Rect;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
		bool m_showDemo{ false };

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, const Rect& srcRect) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const Rect& srcRect) const;

		void DrawRect(float x, float y, float width, float height, const SDL_Color& color = SDL_Color{ 0, 255, 0, 255 }) const;
		void DrawLine(float x1, float y1, float x2, float y2, const SDL_Color& color = SDL_Color{ 0, 255, 0, 255 }) const;
		void DrawMarker(float x, float y, float size, const SDL_Color& color = SDL_Color{ 0, 255, 0, 255 }) const;
		void DrawCircle(float x, float y, float radius, const SDL_Color& color = SDL_Color{0, 255, 0, 255}) const;
		
		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}


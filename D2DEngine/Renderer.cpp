#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

#include "imgui.h"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl2.h>

#include <iostream>

#include "Structs.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void D2D::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void D2D::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	if (m_showDemo)
		ImGui::ShowDemoWindow(&m_showDemo);

	SceneManager::GetInstance().OnGUI();

	ImGui::Render();


	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();

	SDL_RenderPresent(m_renderer);
}

void D2D::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void D2D::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const Rect& srcRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);

	SDL_Rect src{};
	src.x = static_cast<int>(srcRect.x);
	src.y = static_cast<int>(srcRect.y);
	src.w = static_cast<int>(srcRect.w);
	src.h = static_cast<int>(srcRect.h);

	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void D2D::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const Rect& srcRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_Rect src{};
	src.x = static_cast<int>(srcRect.x);
	src.y = static_cast<int>(srcRect.y);
	src.w = static_cast<int>(srcRect.w);
	src.h = static_cast<int>(srcRect.h);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void D2D::Renderer::DrawRect(float x, float y, float width, float height, const SDL_Color& color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	SDL_FRect rect{};
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	SDL_RenderDrawRectF(m_renderer, &rect);
}

void D2D::Renderer::DrawLine(float x1, float y1, float x2, float y2, const SDL_Color& color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
}

void D2D::Renderer::DrawMarker(float x, float y, float size, const SDL_Color& color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	DrawLine(x - size, y, x + size, y, color);
	DrawLine(x, y - size, x, y + size, color);
}

void D2D::Renderer::DrawCircle(float x, float y, float radius, const SDL_Color& color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	float thickness = 1.f;

	for (float i = -radius; i <= radius; i++)
	{
		for (float j = -radius; j <= radius; j++)
		{
			if (i * i + j * j >= (radius - thickness) * (radius - thickness) && i * i + j * j <= (radius + thickness) * (radius + thickness))
			{
				SDL_RenderDrawPointF(m_renderer, x + i, y + j);
			}
		}
	}
}

inline SDL_Renderer* D2D::Renderer::GetSDLRenderer() const { return m_renderer; }

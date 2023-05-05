#pragma once
#include "Structs.h"
#include <memory>

namespace D2D
{
	class Texture2D;
	class RenderComponent;

	class AnimationClip final
	{
	public:
		AnimationClip(RenderComponent* pRenderComponent);

		~AnimationClip() = default;

		AnimationClip(const AnimationClip& other) = delete;
		AnimationClip(AnimationClip&& other) = delete;
		AnimationClip& operator=(const AnimationClip& other) = delete;
		AnimationClip& operator=(AnimationClip&& other) = delete;

		void SetClip(std::shared_ptr<Texture2D> pTexture, int cols, int rows, int frames);

		void SetCurrentSprite();

		void Update();

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		RenderComponent* m_pRenderComponent{};

		int m_Cols{};
		int m_Rows{};

		int m_FrameAmount{};
		int m_CurrentFrame{};

		Rect m_SrcRect{};

		const float m_FrameDuration{ 1 / 3.f };
		float m_FrameTimer{};

		void SetFrame();
	};
}

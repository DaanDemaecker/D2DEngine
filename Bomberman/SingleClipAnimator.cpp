#include "pch.h"
#include "SingleClipAnimator.h"
#include "AnimationClip.h"
#include "RenderComponent.h"
#include "Event.h"

void D2D::SingleClipAnimator::Init(RenderComponent* pRenderComponent, std::shared_ptr<Texture2D> pTexture, int cols, int rows, int frames)
{
	std::unique_ptr<AnimationClip> clip{ std::make_unique<AnimationClip>(pRenderComponent) };
	clip->SetClip(pTexture, cols, rows, frames);

	m_pClips.push_back(std::move(clip));

	m_pClips[m_CurrentClip]->SetCurrentSprite();
}

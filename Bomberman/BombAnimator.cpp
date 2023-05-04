#include "pch.h"
#include "BombAnimator.h"
#include "AnimationClip.h"
#include "RenderComponent.h"

void D2D::BombAnimator::Init(RenderComponent* pRenderComponent, std::shared_ptr<Texture2D> pTexture)
{
	std::unique_ptr<AnimationClip> clip{std::make_unique<AnimationClip>(pRenderComponent)};
	clip->SetClip(pTexture, 3, 1, 3);

	m_pClips.push_back(std::move(clip));

	m_pClips[m_CurrentClip]->SetCurrentSprite();
}

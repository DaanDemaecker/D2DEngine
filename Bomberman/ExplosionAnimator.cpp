#include "pch.h"
#include "ExplosionAnimator.h"
#include "AnimationClip.h"
#include "WorldEvents.h"
#include <iostream>


void D2D::ExplosionAnimator::Init(RenderComponent* pRenderComponent, std::shared_ptr<Texture2D> pTexture)
{
	std::unique_ptr<AnimationClip> clip{ std::make_unique<AnimationClip>(pRenderComponent) };
	clip->SetClip(pTexture, 4, 1, 4);
	clip->AddObserver(this);

	clip->AddAnimationEvent(3, std::make_unique<AnimationFinished>());

	m_pClips.push_back(std::move(clip));

	m_pClips[m_CurrentClip]->SetCurrentSprite();
}

void D2D::ExplosionAnimator::Notify(const Event& event)
{
	if (auto placeBombEvent{ dynamic_cast<const AnimationFinished*>(&event) })
	{
		GetOwner()->Destroy();
	}
}

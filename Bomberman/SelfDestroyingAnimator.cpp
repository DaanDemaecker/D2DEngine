#include "pch.h"
#include "SelfDestroyingAnimator.h"
#include "AnimationClip.h"
#include "WorldEvents.h"
#include <iostream>
#include "SelfDestroyingAnimator.h"

void D2D::SelfDestroyingAnimator::Init(RenderComponent* pRenderComponent, std::shared_ptr<Texture2D> pTexture, int cols, int rows, int frames)
{
	std::unique_ptr<AnimationClip> clip{ std::make_unique<AnimationClip>(pRenderComponent) };
	clip->SetClip(pTexture, cols, rows, frames);
	clip->AddObserver(this);

	clip->AddAnimationEvent(3, std::make_unique<AnimationFinished>());

	m_pClips.push_back(std::move(clip));

	m_pClips[m_CurrentClip]->SetCurrentSprite();
}

void D2D::SelfDestroyingAnimator::Notify(const Event& event)
{
	if (auto placeBombEvent{ dynamic_cast<const AnimationFinished*>(&event) })
	{
		GetOwner()->Destroy();
	}
}

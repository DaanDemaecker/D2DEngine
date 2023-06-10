#include "pch.h"
#include "PlayerAnimator.h"
#include "AnimationClip.h"
#include "RenderComponent.h"
#include "PlayerEvents.h"

#include "ResourceManager.h"

#include <iostream>

void D2D::PlayerAnimator::Init(std::vector<std::shared_ptr<Texture2D>> pSprites, RenderComponent* pRenderComponent, Observer* pObserver)
{
	constexpr float deathClipFrameDuration{ 1 / 5.f };

	if (pSprites.size() < 5)
		return;
	std::unique_ptr<AnimationClip> downClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	downClip->SetClip(pSprites[0], 3, 1, 3);


	std::unique_ptr<AnimationClip> upClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	upClip->SetClip(pSprites[1], 3, 1, 3);


	std::unique_ptr<AnimationClip> leftClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	leftClip->SetClip(pSprites[2], 3, 1, 3);


	std::unique_ptr<AnimationClip> rightClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	rightClip->SetClip(pSprites[3], 3, 1, 3);

	std::unique_ptr<AnimationClip> deathClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	deathClip->SetClip(pSprites[4], 7, 1, 7);
	deathClip->SetFrameDuration(deathClipFrameDuration);
	deathClip->AddAnimationEvent(6, std::move(std::make_unique<PlayerDeathAnimationFinished>()));
	deathClip->AddObserver(pObserver);

	Transition toDownTransition{ 0,std::bind(&D2D::PlayerAnimator::ShouldGoDown, this) };
	upClip->AddTransition(toDownTransition);
	leftClip->AddTransition(toDownTransition);
	rightClip->AddTransition(toDownTransition);

	Transition toUpTransition{ 1,std::bind(&D2D::PlayerAnimator::ShouldGoUp, this) };
	downClip->AddTransition(toUpTransition);
	leftClip->AddTransition(toUpTransition);
	rightClip->AddTransition(toUpTransition);

	Transition toLeftTransition{ 2,std::bind(&D2D::PlayerAnimator::ShouldGoLeft, this) };
	downClip->AddTransition(toLeftTransition);
	upClip->AddTransition(toLeftTransition);
	rightClip->AddTransition(toLeftTransition);

	Transition toRightTransition{ 3,std::bind(&D2D::PlayerAnimator::ShouldGoRight, this) };
	downClip->AddTransition(toRightTransition);
	upClip->AddTransition(toRightTransition);
	leftClip->AddTransition(toRightTransition);

	Transition toDeathTransition{ 4, std::bind(&D2D::PlayerAnimator::IsDead, this) };
	downClip->AddTransition(toDeathTransition);
	upClip->AddTransition(toDeathTransition);
	leftClip->AddTransition(toDeathTransition);
	rightClip->AddTransition(toDeathTransition);

	m_pClips.emplace_back(std::move(downClip));
	m_pClips.emplace_back(std::move(upClip));
	m_pClips.emplace_back(std::move(leftClip));
	m_pClips.emplace_back(std::move(rightClip));
	m_pClips.emplace_back(std::move(deathClip));


	m_pClips[m_CurrentClip]->SetCurrentSprite();
}

bool D2D::PlayerAnimator::ShouldGoDown()
{
	return m_Direction.y > 0;
}

bool D2D::PlayerAnimator::ShouldGoUp()
{
	return m_Direction.y < 0;
}

bool D2D::PlayerAnimator::ShouldGoLeft()
{
	return m_Direction.x < 0;
}

bool D2D::PlayerAnimator::ShouldGoRight()
{
	return m_Direction.x > 0;
}

bool D2D::PlayerAnimator::IsDead()
{
	return m_IsDead;
}

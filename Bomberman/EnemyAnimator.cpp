#include "pch.h"
#include "EnemyAnimator.h"
#include "WorldEvents.h"

void D2D::EnemyAnimator::Init(RenderComponent* pRenderComponent, std::vector<std::shared_ptr<Texture2D>>& pTextures)
{
	if (pTextures.size() < 3)
		GetOwner()->Destroy();


	std::unique_ptr<AnimationClip> leftClip{ std::make_unique<AnimationClip>(pRenderComponent) };

	leftClip->SetClip(pTextures[0], 3, 1, 3);
	m_pClips.push_back(std::move(leftClip));


	std::unique_ptr<AnimationClip> rightClip{ std::make_unique<AnimationClip>(pRenderComponent) };

	rightClip->SetClip(pTextures[1], 3, 1, 3);
	m_pClips.push_back(std::move(rightClip));

	std::unique_ptr<AnimationClip> deathClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	deathClip->SetClip(pTextures[2], 5, 1, 5);
	deathClip->AddAnimationEvent(4, std::make_unique<AnimationFinished>());
	deathClip->AddObserver(this);

	m_pClips.push_back(std::move(deathClip));



	Transition toRightTransition{ 0, 1,std::bind(&D2D::EnemyAnimator::ShouldGoRight, this) };
	m_pTransitions.push_back(toRightTransition);

	Transition toLeftTransition{ 1, 0,std::bind(&D2D::EnemyAnimator::ShouldGoLeft, this) };
	m_pTransitions.push_back(toLeftTransition);


	Transition leftToDeathTransition{ 0, 2,std::bind(&D2D::EnemyAnimator::IsDead, this) };
	m_pTransitions.push_back(leftToDeathTransition);

	Transition rightToDeathTransition{ 1, 2,std::bind(&D2D::EnemyAnimator::IsDead, this) };
	m_pTransitions.push_back(rightToDeathTransition);



	m_pClips[m_CurrentClip]->SetCurrentSprite();
}

bool D2D::EnemyAnimator::ShouldGoLeft()
{
	return !m_FacingRight;
}

bool D2D::EnemyAnimator::ShouldGoRight()
{
	return m_FacingRight;
}

bool D2D::EnemyAnimator::IsDead()
{
	return m_IsDead;
}

void D2D::EnemyAnimator::Notify(const Event& event)
{
	if (auto placeBombEvent{ dynamic_cast<const AnimationFinished*>(&event) })
	{
		GetOwner()->Destroy();
	}
}
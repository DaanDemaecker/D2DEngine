#include "pch.h"
#include "PlayerAnimator.h"
#include "AnimationClip.h"
#include "RenderComponent.h"
#include "Event.h"

#include "ResourceManager.h"

#include <iostream>

void D2D::PlayerAnimator::Init(RenderComponent* pRenderComponent)
{
	auto downTexture = ResourceManager::GetInstance().LoadTexture("Sprites/SpriteSheets/Player/PlayerDown.png");
	std::unique_ptr<AnimationClip> downClip{ std::make_unique<AnimationClip>(pRenderComponent) };

	downClip->SetClip(downTexture, 3, 1, 3);
	m_pClips.push_back(std::move(downClip));


	auto upTexture = ResourceManager::GetInstance().LoadTexture("Sprites/SpriteSheets/Player/PlayerUp.png");
	std::unique_ptr<AnimationClip> upClip{ std::make_unique<AnimationClip>(pRenderComponent) };

	upClip->SetClip(upTexture, 3, 1, 3);
	m_pClips.push_back(std::move(upClip));


	auto leftTexture = ResourceManager::GetInstance().LoadTexture("Sprites/SpriteSheets/Player/PlayerLeft.png");
	std::unique_ptr<AnimationClip> leftClip{ std::make_unique<AnimationClip>(pRenderComponent) };

	leftClip->SetClip(leftTexture, 3, 1, 3);
	m_pClips.push_back(std::move(leftClip));


	auto rightTexture = ResourceManager::GetInstance().LoadTexture("Sprites/SpriteSheets/Player/PlayerRight.png");
	std::unique_ptr<AnimationClip> rightClip{ std::make_unique<AnimationClip>(pRenderComponent) };

	rightClip->SetClip(rightTexture, 3, 1, 3);
	m_pClips.push_back(std::move(rightClip));



	Transition toDownTransition{ -1, 0,std::bind(&D2D::PlayerAnimator::ShouldGoDown, this) };
	m_pTransitions.push_back(toDownTransition);

	Transition toUpTransition{-1, 1,std::bind(&D2D::PlayerAnimator::ShouldGoUp, this) };
	m_pTransitions.push_back(toUpTransition);

	Transition toLeftTransition{ -1, 2,std::bind(&D2D::PlayerAnimator::ShouldGoLeft, this) };
	m_pTransitions.push_back(toLeftTransition);

	Transition toRightTransition{ -1, 3,std::bind(&D2D::PlayerAnimator::ShouldGoRight, this) };
	m_pTransitions.push_back(toRightTransition);


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

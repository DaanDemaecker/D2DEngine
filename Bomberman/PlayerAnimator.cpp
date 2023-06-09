#include "pch.h"
#include "PlayerAnimator.h"
#include "AnimationClip.h"
#include "RenderComponent.h"
#include "Event.h"

#include "ResourceManager.h"

#include <iostream>

void D2D::PlayerAnimator::Init(RenderComponent* pRenderComponent)
{
	//constexpr float deathClipFrameDuration{ 1 / 5.f };

	auto downTexture = ResourceManager::GetInstance().LoadTexture("Sprites/SpriteSheets/Player/PlayerDown.png");
	std::unique_ptr<AnimationClip> downClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	downClip->SetClip(downTexture, 3, 1, 3);


	auto upTexture = ResourceManager::GetInstance().LoadTexture("Sprites/SpriteSheets/Player/PlayerUp.png");
	std::unique_ptr<AnimationClip> upClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	upClip->SetClip(upTexture, 3, 1, 3);


	auto leftTexture = ResourceManager::GetInstance().LoadTexture("Sprites/SpriteSheets/Player/PlayerLeft.png");
	std::unique_ptr<AnimationClip> leftClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	leftClip->SetClip(leftTexture, 3, 1, 3);


	auto rightTexture = ResourceManager::GetInstance().LoadTexture("Sprites/SpriteSheets/Player/PlayerRight.png");
	std::unique_ptr<AnimationClip> rightClip{ std::make_unique<AnimationClip>(pRenderComponent) };
	rightClip->SetClip(rightTexture, 3, 1, 3);

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


	m_pClips.push_back(std::move(downClip));
	m_pClips.push_back(std::move(upClip));
	m_pClips.push_back(std::move(leftClip));
	m_pClips.push_back(std::move(rightClip));



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

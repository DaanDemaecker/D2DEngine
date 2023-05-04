#include "AnimationController.h"
#include "AnimationClip.h"

void D2D::AnimationController::SetShouldAnimate(bool shouldAnimate)
{
	m_ShouldAnimate = shouldAnimate;
}

void D2D::AnimationController::Update()
{
	for (auto& transition : m_pTransitions)
	{
		if (transition->fromClip != m_CurrentClip)
			continue;
		else
		{
			if (transition->predicate)
			{
				m_CurrentClip = transition->toClip;
				m_pClips[m_CurrentClip]->SetCurrentSprite();
			}
		}
	}

	if (m_ShouldAnimate && m_CurrentClip < m_pClips.size())
	{
		m_pClips[m_CurrentClip]->Update();
	}
}
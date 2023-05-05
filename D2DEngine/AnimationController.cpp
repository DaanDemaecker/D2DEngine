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
		if (transition.fromClip != -1 && transition.fromClip != m_CurrentClip && transition.toClip == m_CurrentClip)
			continue;
		else
		{
			if (transition.predicate())
			{
				m_CurrentClip = transition.toClip;
				if(m_CurrentClip < static_cast<int>(m_pClips.size()))
					m_pClips[m_CurrentClip]->SetCurrentSprite();
				break;
			}
		}
	}

	if (m_ShouldAnimate && m_CurrentClip < static_cast<int>(m_pClips.size()))
	{
		m_pClips[m_CurrentClip]->Update();
	}
}
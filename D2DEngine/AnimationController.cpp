#include "AnimationController.h"
#include "AnimationClip.h"
#include "Event.h"

void D2D::AnimationController::SetShouldAnimate(bool shouldAnimate)
{
	m_ShouldAnimate = shouldAnimate;
}

void D2D::AnimationController::Update()
{
	auto transitions = m_pClips[m_CurrentClip]->GetTransitions();

	for (auto& transition : transitions)
	{
		if (transition.predicate())
		{
			m_CurrentClip = transition.toClip;
			if (m_CurrentClip < static_cast<int>(m_pClips.size()))
				m_pClips[m_CurrentClip]->SetCurrentSprite();
			break;
		}
	}

	if (m_ShouldAnimate && m_CurrentClip < static_cast<int>(m_pClips.size()))
	{
		m_pClips[m_CurrentClip]->Update();
	}
}
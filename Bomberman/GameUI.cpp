#include "pch.h"
#include "GameUI.h"
#include "PlayerEvents.h"

void D2D::GameUI::Initialize(GameObject* pIntroScreenObject, GameObject* pHud, GameObject* pPlayfieldObject,
	Observer* pPointsDisplay, Observer* pLivesDisplay, GameObject* pGameOverScreen)
{
	if (pHud != nullptr)
	{
		pHud->SetActive(false);
	}

	if (pPlayfieldObject != nullptr)
	{
		pPlayfieldObject->SetActive(false);
	}

	m_pIntroState = std::make_unique<IntroState>();
	m_pPlayingState = std::make_unique<PlayingState>();
	m_pGameOverState = std::make_unique<GameOverState>();

	m_pIntroState->SetVariables(pIntroScreenObject, pPlayfieldObject, m_pPlayingState.get(), pPointsDisplay, pLivesDisplay);
	m_pPlayingState->SetVariables(pHud, pPlayfieldObject);
	m_pGameOverState->SetVariables(pGameOverScreen);

	m_pState = m_pIntroState.get();
}

void D2D::GameUI::OnSceneLoad()
{
	SetState(m_pIntroState.get());
}

void D2D::GameUI::Update()
{
	if (m_pState != nullptr)
	{
		m_pState->Update();

		m_pState->ChangeState(this);
	}
}

void D2D::GameUI::SetState(GameUIState* pNewState)
{
	if (pNewState != nullptr)
	{
		if (m_pState != nullptr)
		{
			m_pState->OnStateLeave();
		}

		m_pState = pNewState;

		m_pState->OnStateEnter();
	}
}

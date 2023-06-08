#include "pch.h"
#include "GameUI.h"

void D2D::GameUI::Initialize(GameObject* pIntroScreenObject, GameObject* pHud, GameObject* pPlayfieldObject, GameObject* pEnemyManager)
{
	if (pHud != nullptr)
	{
		pHud->SetActive(false);
	}

	if (pPlayfieldObject != nullptr)
	{
		pPlayfieldObject->SetActive(false);
	}

	if (pEnemyManager != nullptr)
	{
		pEnemyManager->SetActive(false);
	}

	m_pIntroState = std::make_unique<IntroState>();
	m_pIntroState->SetVariables(pIntroScreenObject);

	m_pPlayingState = std::make_unique<PlayingState>();
	m_pPlayingState->SetVariables(pHud, pPlayfieldObject, pEnemyManager);

	m_pState = m_pIntroState.get();
}

void D2D::GameUI::OnSceneLoad()
{
	if (m_pState != nullptr)
	{
		m_pState->OnStateEnter();
	}
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

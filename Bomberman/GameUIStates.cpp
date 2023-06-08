#include "pch.h"
#include "GameUIStates.h"
#include "GameUI.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "TimeManager.h"

#pragma region IntroState
void D2D::IntroState::SetVariables(GameObject* pIntroScreen)
{
	m_pIntroScreen = pIntroScreen;
}

void D2D::IntroState::Update()
{
	m_Timer -= TimeManager::GetInstance().GetDeltaTime();
}

void D2D::IntroState::ChangeState(GameUI* gameUI)
{
	if (m_Timer <= 0)
	{
		gameUI->SetState(gameUI->GetPlayingState());
	}
}

void D2D::IntroState::OnStateEnter()
{
	if (m_pIntroScreen != nullptr)
	{
		m_pIntroScreen->SetActive(true);
	}

	m_Timer = m_Time;

	ServiceLocator::GetSoundSystem().Play(6, 128, 0);
}

void D2D::IntroState::OnStateLeave()
{
	if (m_pIntroScreen != nullptr)
	{
		m_pIntroScreen->SetActive(false);
	}
}
#pragma endregion IntroState


#pragma region PlayingState
void D2D::PlayingState::SetVariables(GameObject* pHud, GameObject* pPlayField, GameObject* pEnemyManager)
{
	m_pHud = pHud;
	m_pPlayField = pPlayField;
	m_pEnemyManager = pEnemyManager;
}

void D2D::PlayingState::Update()
{

}

void D2D::PlayingState::OnStateEnter()
{
	ServiceLocator::GetSoundSystem().Play(0, 128, -1);

	if (m_pHud != nullptr)
		m_pHud->SetActive(true);

	if (m_pPlayField != nullptr)
		m_pPlayField->SetActive(true);

	if (m_pEnemyManager != nullptr)
		m_pEnemyManager->SetActive(true);
}

void D2D::PlayingState::OnStateLeave()
{
	ServiceLocator::GetSoundSystem().StopMusic();

	if (m_pHud != nullptr)
		m_pHud->SetActive(false);

	if (m_pPlayField != nullptr)
		m_pPlayField->SetActive(false);

	if (m_pEnemyManager != nullptr)
		m_pEnemyManager->SetActive(false);
}
#pragma endregion PlayingState

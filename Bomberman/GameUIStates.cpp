#include "pch.h"
#include "GameUIStates.h"
#include "GameUI.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "TimeManager.h"
#include "GridComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerEvents.h"
#include "InputManager.h"

#pragma region IntroState
void D2D::IntroState::SetVariables(GameObject* pIntroScreen, GameObject* pPlayfield,
	Observer* pPlayingStateObserver, Observer* pPointsDisplay, Observer* pLivesDisplay)
{
	m_pIntroScreen = pIntroScreen;
	m_pGrid = pPlayfield->GetComponent<GridComponent>().get();
	m_pPlayingStateObserver = pPlayingStateObserver;
	m_pPointsDisplay = pPointsDisplay;
	m_pLivesDisplay = pLivesDisplay;
}

void D2D::IntroState::Update()
{
	m_Timer -= TimeManager::GetInstance().GetDeltaTime();
}

void D2D::IntroState::ChangeState(GameUI* gameUI)
{
	if (m_Timer <= 0)
	{
		m_LoadLevelThread.join();
		gameUI->SetState(gameUI->GetPlayingState());
	}
}

void D2D::IntroState::OnStateEnter()
{
	if (m_pIntroScreen != nullptr)
	{
		m_pIntroScreen->SetActive(true);
	}

	if (m_pGrid != nullptr)
	{
		constexpr float gridSize{ 34.f };
		m_LoadLevelThread = std::jthread(&GridComponent::SetupGame, m_pGrid, "../Data/TextFiles/Level.txt", gridSize,
			m_pPlayingStateObserver, m_pLivesDisplay, m_pPointsDisplay,
			D2D::SceneManager::GetInstance().GetActiveScene()->GetName());
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
void D2D::PlayingState::SetVariables(GameObject* pHud, GameObject* pPlayField)
{
	m_pHud = pHud;
	m_pPlayField = pPlayField;
}

void D2D::PlayingState::Update()
{

}

void D2D::PlayingState::ChangeState(GameUI* gameUI)
{
	if (m_ShouldRestart)
	{
		gameUI->SetState(gameUI->GetIntroState());
	}
}

void D2D::PlayingState::OnStateEnter()
{
	ServiceLocator::GetSoundSystem().Play(0, 128, -1);

	m_ShouldRestart = false;

	if (m_pHud != nullptr)
		m_pHud->SetActive(true);

	if (m_pPlayField != nullptr)
		m_pPlayField->SetActive(true);
}

void D2D::PlayingState::OnStateLeave()
{
	ServiceLocator::GetSoundSystem().StopMusic();

	if (m_pHud != nullptr)
		m_pHud->SetActive(false);

	if (m_pPlayField != nullptr)
	{
		m_pPlayField->GetComponent<GridComponent>()->EndGame();
		m_pPlayField->SetActive(false);
	}

	InputManager::GetInstance().RemoveCommands(SceneManager::GetInstance().GetActiveScene()->GetName());
}

void D2D::PlayingState::Notify(const Event& event)
{
	if (auto animationFinishedEvent{ dynamic_cast<const PlayerDeathAnimationFinished*>(&event) })
	{
			m_ShouldRestart = true;
	}
}
#pragma endregion PlayingState

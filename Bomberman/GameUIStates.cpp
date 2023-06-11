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
#include "GameData.h"
#include "WorldEvents.h"
#include "TextComponent.h"
#include "InputManager.h"
#include "FunctionCommand.h"

#pragma region IntroState
void D2D::IntroState::SetVariables(GameObject* pIntroScreen, GameObject* pPlayfield,
	Observer* pPlayingStateObserver, Observer* pPointsDisplay, Observer* pLivesDisplay, Subject* pTimer,
	TextComponent* pText)
{
	m_pIntroScreen = pIntroScreen;
	m_pGrid = pPlayfield->GetComponent<GridComponent>().get();
	m_pPlayingStateObserver = pPlayingStateObserver;
	m_pPointsDisplay = pPointsDisplay;
	m_pLivesDisplay = pLivesDisplay;
	m_pTextComponent = pText;
	m_pTimer = pTimer;
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

	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetText("STAGE " + std::to_string(GameData::GetInstance().GetCurrentLevel()));
	}

	if (m_pGrid != nullptr)
	{
		constexpr float gridSize{ 34.f };
		m_LoadLevelThread = std::jthread(&GridComponent::SetupGame, m_pGrid, "../Data/TextFiles/Level" + std::to_string(GameData::GetInstance().GetCurrentLevel()) +".txt", gridSize,
			m_pPlayingStateObserver, m_pLivesDisplay, m_pPointsDisplay, m_pTimer,
			D2D::SceneManager::GetInstance().GetActiveScene()->GetName());
	}

	m_Timer = m_Time;

	NotifyObservers(StartGameEvent());

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
	if (m_LevelEnd)
	{
		gameUI->SetState(gameUI->GetLevelEndState());
	}

	if (m_ShouldRestart)
	{
		if (GameData::GetInstance().GetLivesAmount() < 0)
		{
			gameUI->SetState(gameUI->GetGameOverState());
		}
		else
		{
			gameUI->SetState(gameUI->GetIntroState());
		}
	}
}

void D2D::PlayingState::OnStateEnter()
{
	ServiceLocator::GetSoundSystem().Play(0, 128, -1);
	InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_F1, keyState::Down,
		std::make_unique<FunctionCommand>(std::bind(&D2D::PlayingState::Notify, this, LevelCompleteEvent())),
		SceneManager::GetInstance().GetActiveScene()->GetName());

	m_ShouldRestart = false;
	m_LevelEnd = false;

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
	SceneManager::GetInstance().GetActiveScene()->BindInfoWindowCommand();
}

void D2D::PlayingState::Notify(const Event& event)
{
	if (m_LevelEnd || m_ShouldRestart)
		return;

	if (auto levelEndEvent{ dynamic_cast<const LevelCompleteEvent*>(&event) })
	{
		int level{ GameData::GetInstance().GetCurrentLevel() };
		
		if (level == GameData::GetInstance().GetMaxLevel())
		{
			m_LevelEnd = true;
		}
		else
		{
			m_ShouldRestart = true;
			GameData::GetInstance().SetCurrentLevel(level + 1);
		}
	}
	else if (auto animationFinishedEvent{ dynamic_cast<const PlayerDeathAnimationFinished*>(&event) })
	{
		m_ShouldRestart = true;
	}
}
#pragma endregion PlayingState


#pragma region GameOver
void D2D::GameOverState::SetVariables(GameObject* pGameOverScreen)
{
	m_pGameOverScreen = pGameOverScreen;
}

void D2D::GameOverState::Update()
{
	m_Timer -= TimeManager::GetInstance().GetDeltaTime();
	if (m_Timer <= 0)
	{
		if (GameData::GetInstance().GetGameMode() == GameMode::SinglePlayer)
		{
			SceneManager::GetInstance().NextScene();
		}
		else
		{
			SceneManager::GetInstance().PreviousScene();
		}
	}
}

void D2D::GameOverState::OnStateEnter()
{
	ServiceLocator::GetSoundSystem().Play(8, 128, 0);
	m_Timer = m_Time;

	GameData::GetInstance().SetCurrentLevel(1);

	if (m_pGameOverScreen)
	{
		m_pGameOverScreen->SetActive(true);
	}
}

void D2D::GameOverState::OnStateLeave()
{
	if (m_pGameOverScreen)
	{
		m_pGameOverScreen->SetActive(false);
	}
}
#pragma endregion


#pragma region LevelEnd
void D2D::LevelEndState::SetVariables(GameObject* pLevelEndScreen)
{
	m_pLevelEndcreen = pLevelEndScreen;
}

void D2D::LevelEndState::Update()
{
	m_Timer -= TimeManager::GetInstance().GetDeltaTime();
	if (m_Timer <= 0)
	{
		if (GameData::GetInstance().GetGameMode() == GameMode::SinglePlayer)
		{
			GameData::GetInstance().SetCurrentLevel(1);
			SceneManager::GetInstance().NextScene();
		}
		else
		{
			GameData::GetInstance().SetCurrentLevel(1);
			SceneManager::GetInstance().PreviousScene();
		}
	}
}

void D2D::LevelEndState::OnStateEnter()
{
	m_Timer = m_Time;
	if (m_pLevelEndcreen != nullptr)
	{
		m_pLevelEndcreen->SetActive(true);
	}
	ServiceLocator::GetSoundSystem().Play(12, 128, 0);
}

void D2D::LevelEndState::OnStateLeave()
{
	if (m_pLevelEndcreen != nullptr)
	{
		m_pLevelEndcreen->SetActive(false);
	}
}

#pragma endregion LevelEnd

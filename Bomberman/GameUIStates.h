#pragma once
#include "State.h"
#include "Observer.h"
#include <thread>
#include "Subject.h"

namespace D2D
{
	class GameUI;
	class GameObject;
	class GridComponent;
	class TextComponent;

	class GameUIState : public State
	{
	public:

		virtual void ChangeState(GameUI* manager) = 0;
	};

	class IntroState final : public GameUIState, public Subject
	{
	public:
		IntroState() = default;
		~IntroState() = default;

		void SetVariables( GameObject * pIntroScreen, GameObject* pPlayfield,
			Observer* pPlayingStateObserver, Observer* pPointsDisplay, Observer* pLivesDisplay,
			TextComponent* pText);

		virtual void Update() override;

		virtual void ChangeState(GameUI* gameUI) override;

		virtual void OnStateEnter() override;
		virtual void OnStateLeave() override;

	private:
		GameObject* m_pIntroScreen{ nullptr };
		GridComponent* m_pGrid{ nullptr };


		TextComponent* m_pTextComponent{};

		Observer* m_pPlayingStateObserver{ nullptr };
		Observer* m_pPointsDisplay{ nullptr };
		Observer* m_pLivesDisplay{ nullptr };

		std::jthread m_LoadLevelThread{};

		float m_Timer{};
		const float m_Time{ 3.0f };

	};

	class PlayingState final : public GameUIState, public Observer
	{
	public:
		PlayingState() = default;
		~PlayingState() = default;

		void SetVariables(GameObject* pHud, GameObject* pPlayField);

		virtual void Update() override;

		virtual void ChangeState(GameUI* gameUI) override;

		virtual void OnStateEnter() override;
		virtual void OnStateLeave() override;

		virtual void Notify(const Event& event);

	private:
		bool m_ShouldRestart{ false };
		bool m_LevelEnd{ false };


		GameObject* m_pHud{ nullptr };
		GameObject* m_pPlayField{ nullptr };
	};

	class GameOverState final : public GameUIState
	{
	public:
		GameOverState() = default;
		~GameOverState() = default;

		void SetVariables(GameObject* pGameOverScreen);

		virtual void Update() override;

		virtual void ChangeState(GameUI*) override {};

		virtual void OnStateEnter() override;
		virtual void OnStateLeave() override;

	private:
		float m_Timer{};
		const float m_Time{ 7.0f };

		GameObject* m_pGameOverScreen{};
	};

	class LevelEndState final : public GameUIState
	{
	public:
		LevelEndState() = default;
		~LevelEndState() = default;

		void SetVariables(GameObject* pLevelEndScreen);

		virtual void Update() override;

		virtual void ChangeState(GameUI*) override {};

		virtual void OnStateEnter() override;
		virtual void OnStateLeave() override;

	private:
		float m_Timer{};
		const float m_Time{ 13.0f };

		GameObject* m_pLevelEndcreen{};
	};
}


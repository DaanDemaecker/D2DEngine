#pragma once
#include "State.h"
#include "Observer.h"
#include <thread>

namespace D2D
{
	class GameUI;
	class GameObject;
	class GridComponent;

	class GameUIState : public State
	{
	public:

		virtual void ChangeState(GameUI* manager) = 0;
	};

	class IntroState final : public GameUIState
	{
	public:
		IntroState() = default;
		~IntroState() = default;

		void SetVariables( GameObject * pIntroScreen, GameObject* pPlayfield,
			Observer* pPlayingStateObserver, Observer* pPointsDisplay, Observer* pLivesDisplay);

		virtual void Update() override;

		virtual void ChangeState(GameUI* gameUI) override;

		virtual void OnStateEnter() override;
		virtual void OnStateLeave() override;

	private:
		GameObject* m_pIntroScreen{ nullptr };
		GridComponent* m_pGrid{ nullptr };

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

		GameObject* m_pHud{ nullptr };
		GameObject* m_pPlayField{ nullptr };
	};
}


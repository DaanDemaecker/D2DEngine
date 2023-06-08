#pragma once
#include "State.h"


namespace D2D
{
	class GameUI;
	class GameObject;

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

		void SetVariables( GameObject * pIntroScreen );

		virtual void Update() override;

		virtual void ChangeState(GameUI* gameUI) override;

		virtual void OnStateEnter() override;
		virtual void OnStateLeave() override;

	private:
		GameObject* m_pIntroScreen{ nullptr };

		float m_Timer{};
		const float m_Time{ 3.0f };

	};

	class PlayingState final : public GameUIState
	{
	public:
		PlayingState() = default;
		~PlayingState() = default;

		void SetVariables(GameObject* pHud, GameObject* pPlayField, GameObject* pEnemyManager);

		virtual void Update() override;

		virtual void ChangeState(GameUI*) override {};

		virtual void OnStateEnter() override;
		virtual void OnStateLeave() override;

	private:
		GameObject* m_pHud{ nullptr };
		GameObject* m_pPlayField{ nullptr };
		GameObject* m_pEnemyManager{ nullptr };
	};
}


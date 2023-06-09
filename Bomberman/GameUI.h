#pragma once
#include "Component.h"
#include "GameUIStates.h"

namespace D2D
{
	class Observer;

	class GameUI final : public Component
	{
	public:
		GameUI() = default;
		virtual ~GameUI() = default;

		void Initialize(GameObject* pIntroScreenObject, GameObject* pHud, GameObject* pPlayfieldObject, Observer* pPointsDisplay, Observer* pLivesDisplay, GameObject* pGameOverScreen);

		virtual void OnSceneLoad() override;

		virtual void Update() override;

		void SetState(GameUIState* pNewState);

		GameUIState* GetIntroState(){ return m_pIntroState.get(); }
		GameUIState* GetPlayingState() { return m_pPlayingState.get(); }
		GameUIState* GetGameOverState() { return m_pGameOverState.get(); }

	private:
		GameUIState* m_pState{};

		std::unique_ptr<IntroState> m_pIntroState{};
		std::unique_ptr<PlayingState> m_pPlayingState{};
		std::unique_ptr<GameOverState> m_pGameOverState{};
	};
}


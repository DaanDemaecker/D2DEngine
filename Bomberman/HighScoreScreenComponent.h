#pragma once
#include "Component.h"
#include "HighScoreStates.h"
#include <string>

namespace D2D
{
	class Texture2D;
	class TextComponent;

	class HighScoreScreenComponent final : public Component
	{
	public:
		HighScoreScreenComponent() = default;
		virtual ~HighScoreScreenComponent() override;

		void Initialize(GameObject* pInputWindow, GameObject* pHighscoresWindow);

		virtual void OnSceneLoad();
		virtual void OnSceneUnload();

		virtual void Update() override;

		void SetState(HighScoreStates* pNewState);
		InputState* GetInputState() {return m_pInputState.get();}
		HighscoresState* GetHighscoresState() { return m_pHighscoresState.get(); }

	private:
		TextComponent* m_pTextComponent{};

		HighScoreStates* m_pState{};
		std::unique_ptr<InputState> m_pInputState{};
		std::unique_ptr<HighscoresState>  m_pHighscoresState{};

		void SetupInputState(GameObject* pInputWindow);

		void AddArrows(GameObject* pLetter, std::shared_ptr<Texture2D> upArrow, std::shared_ptr<Texture2D> downArrow);

		
	};
}
#pragma once
#include "State.h"
#include "Observer.h"
#include <thread>
#include "Subject.h"
#include <string>
#include <glm/glm.hpp>

namespace D2D
{
	class HighScoreScreenComponent;
	class GameObject;
	class GridComponent;
	class TextComponent;

	class HighScoreStates : public State
	{
	public:

		virtual void ChangeState(HighScoreScreenComponent* highScoreUI) = 0;
	};

	class InputState final : public HighScoreStates
	{
	public:
		InputState() = default;
		~InputState() = default;

		void SetVariables(GameObject* screen, TextComponent* text1, TextComponent* text2, TextComponent* text3, TextComponent* done);

		virtual void Update() override {};

		void HorizontalScroll(int direction);
		void VerticalScroll(int direction);

		void Continue();

		virtual void ChangeState(HighScoreScreenComponent* highScoreUI) override;

		virtual void OnStateEnter() override;
		virtual void OnStateLeave() override;

	public:
		bool m_Active{ false };
		GameObject* m_pScreen{};

		const glm::vec3 m_Yellow{ 253.f, 255.f, 32.f };
		const glm::vec3 m_White{ 255.f, 255.f, 255.f };

		bool m_Continue{ false };

		int m_Selected{};
		std::vector<TextComponent*> m_pLetters{};
		TextComponent* m_pDone{};
	};

	class HighscoresState final : public HighScoreStates
	{
	public:
		HighscoresState() = default;
		~HighscoresState() = default;

		void SetVariables(GameObject* pScreen);

		virtual void Update() override {};

		virtual void ChangeState(HighScoreScreenComponent* /*highScoreUI*/) override {};

		virtual void OnStateEnter() override;
		virtual void OnStateLeave() override;

		void Continue();
	private:
		bool m_Active{ false };

		GameObject* m_pScreen{};

		void SetupScores();
		
		void CreateScoreBoard(std::vector<std::pair<int, std::string>>& entries, std::pair<int, std::string> entry);

		void ReadFromFile(const std::string& fileName, std::vector<std::pair<int, std::string>>& entries);
		void WriteToFile(const std::string& fileName, std::vector<std::pair<int, std::string>>& entries);
	};
}


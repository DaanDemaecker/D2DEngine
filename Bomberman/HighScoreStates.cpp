#include "pch.h"
#include "HighScoreStates.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "FunctionCommand.h"
#include "TextComponent.h"
#include "HighScoreScreenComponent.h"
#include "GameData.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "glm/glm.hpp"
#include <fstream>
#include <algorithm>
#include <regex>

extern SDL_Window* g_window;

#pragma region InputState
void D2D::InputState::SetVariables(GameObject* screen, TextComponent* text1, TextComponent* text2, TextComponent* text3, TextComponent* done, GameObject* selector)
{
	m_pScreen = screen;

	m_Selected = 0;
	m_pLetters.push_back(text1);
	m_pLetters.push_back(text2);
	m_pLetters.push_back(text3);
	m_pDone = done;
	m_pSelector = selector;

	auto& pInputManager{ InputManager::GetInstance() };

	const std::string sceneName{"HighscoreScreen"};

	pInputManager.AddKeyboardCommand(SDL_SCANCODE_LEFT, keyState::Down, std::make_unique<D2D::FunctionCommand>(std::bind(&D2D::InputState::HorizontalScroll, this, -1)), sceneName);
	pInputManager.AddKeyboardCommand(SDL_SCANCODE_RIGHT, keyState::Down, std::make_unique<D2D::FunctionCommand>(std::bind(&D2D::InputState::HorizontalScroll, this, 1)), sceneName);
	pInputManager.AddKeyboardCommand(SDL_SCANCODE_DOWN, keyState::Down, std::make_unique<D2D::FunctionCommand>(std::bind(&D2D::InputState::VerticalScroll, this, 1)), sceneName);
	pInputManager.AddKeyboardCommand(SDL_SCANCODE_UP, keyState::Down, std::make_unique<D2D::FunctionCommand>(std::bind(&D2D::InputState::VerticalScroll, this, -1)), sceneName);
	pInputManager.AddKeyboardCommand(SDL_SCANCODE_SPACE, keyState::Down, std::make_unique<D2D::FunctionCommand>(std::bind(&D2D::InputState::Continue, this)), sceneName);
}

void D2D::InputState::HorizontalScroll(int direction)
{
	if (!m_Active)
		return;

	int oldSelection{ m_Selected };
	m_Selected = (m_Selected + direction) % 4;
	if (m_Selected < 0)
		m_Selected = 3;

	if (oldSelection == 3)
	{
		if (m_pDone != nullptr)
		{
			m_pDone->SetColor(255.f, 255.f, 255.f);
		}

		if (m_pSelector != nullptr)
		{
			m_pSelector->SetActive(true);
		}
	}

	if (m_Selected == 3)
	{
		if (m_pDone != nullptr)
		{
			m_pDone->SetColor(253.f, 255.f, 32.f);
		}

		if (m_pSelector != nullptr)
		{
			m_pSelector->SetActive(false);
		}
	}

	if (m_pSelector != nullptr && m_Selected < static_cast<int>(m_pLetters.size()))
	{
		m_pSelector->SetActive(true);
		m_pSelector->SetParent(m_pLetters[m_Selected]->GetOwner(), false);
	}
	
}

void D2D::InputState::VerticalScroll(int direction)
{
	if (!m_Active || m_Selected >= static_cast<int>(m_pLetters.size()))
		return;

	auto text{ m_pLetters[m_Selected]->GetText() };
	char letter{'A'};
	if (text.size() > 0)
	{
		letter = text[0];
	}

	if (direction < 0)
	{
		letter--;
	}
	else
	{
		letter++;
	}

	if (letter < 'A')letter = 'Z';
	else if (letter > 'Z') letter = 'A';
	
	m_pLetters[m_Selected]->SetText(std::string(1, letter));
}

void D2D::InputState::Continue()
{
	if (m_Active && m_Selected == 3)
		m_Continue = true;
}

void D2D::InputState::ChangeState(HighScoreScreenComponent* highScoreUI)
{
	if (m_Continue)
	{
		highScoreUI->SetState(highScoreUI->GetHighscoresState());
	}
}

void D2D::InputState::OnStateEnter()
{
	m_Active = true;
	if (m_pScreen != nullptr)
	{
		m_pScreen->SetActive(true);
	}
	m_Selected = 0;
	if (m_pSelector != nullptr && m_pLetters.size() > 0)
	{
		m_pSelector->SetActive(true);
		m_pSelector->SetParent(m_pLetters[0]->GetOwner(), false);
	}
	for (auto& letter : m_pLetters)
	{
		letter->SetText("A");
	}
	if (m_pDone != nullptr)
	{
		m_pDone->SetColor(255.f, 255.f, 255.f);
	}

}

void D2D::InputState::OnStateLeave()
{
	m_Continue = false;
	m_Active = false;
	if (m_pScreen != nullptr)
	{
		m_pScreen->SetActive(false);
	}

	std::string name{};
	for (auto& text : m_pLetters)
	{
		name += text->GetText();
	}

	GameData::GetInstance().SetName(name);
}
#pragma endregion Input

#pragma region Highscores


#pragma endregion HighScores

void D2D::HighscoresState::SetVariables(GameObject* pScreen)
{
	m_pScreen = pScreen;
	const std::string sceneName{ "HighscoreScreen" };
	InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_SPACE, keyState::Down, std::make_unique<FunctionCommand>(std::bind(&HighscoresState::Continue, this)), sceneName);
}

void D2D::HighscoresState::OnStateEnter()
{
	m_Active = true;
	if (m_pScreen == nullptr)
		return;

	m_pScreen->SetActive(true);

	SetupScores();
}

void D2D::HighscoresState::OnStateLeave()
{
	m_Active = false;
	if (m_pScreen == nullptr)
		return;

	m_pScreen->RemoveAllChildren();
	m_pScreen->SetActive(false);
}

void D2D::HighscoresState::Continue()
{
	if (!m_Active)
		return;

	SceneManager::GetInstance().NextScene();
}

void D2D::HighscoresState::SetupScores()
{
	const std::string fileName{ ResourceManager::GetInstance().GetPath() + "/TextFiles/HighScores.txt" };

	std::vector<std::pair<int, std::string>> entries{};

	ReadFromFile(fileName, entries);

	std::string name{ GameData::GetInstance().GetName() };
	int score{ GameData::GetInstance().GetScore() };
	std::pair<int, std::string> entry{ std::make_pair(score, name) };

	entries.emplace_back(entry);
	std::sort(entries.begin(), entries.end(), [](const auto& a, const auto& b)
		{
		return a.first > b.first;
		});

	while (entries.size() > 10)
	{
		entries.pop_back();
	}

	CreateScoreBoard(entries, entry);

	WriteToFile(fileName, entries);
}

void D2D::HighscoresState::CreateScoreBoard(std::vector<std::pair<int, std::string>>& entries, std::pair<int, std::string> entry)
{
	if (m_pScreen == nullptr)
		return;

	auto& pResourceManager{ ResourceManager::GetInstance() };
	const auto pBigFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 50) };
	const auto pSmallFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 30) };

	int windowWidth{}, windowHeight{};
	SDL_GetWindowSize(g_window, &windowWidth, &windowHeight);

	constexpr float step{ 40 };

	const auto highScoreObject{m_pScreen->CreateNewObject("Highscore")};
	highScoreObject->GetTransform()->SetWorldPosition(static_cast<float>(windowWidth)/2 - 200, 10);

	auto highscoreRender = highScoreObject->AddComponent<RenderComponent>();
	auto highscoreText = highScoreObject->AddComponent<TextComponent>();
	highscoreText->SetFont(pBigFont);
	highscoreText->SetText("HIGH-SCORES");
	highscoreText->SetColor(255.f, 255.f, 255.f);
	
	glm::vec2 leftPos{ static_cast<float>(windowWidth) / 2 - 100, 55 };
	glm::vec2 rightPos{ static_cast<float>(windowWidth) / 2, 55};

	for (auto& pair : entries)
	{
		const auto nameObject{ m_pScreen->CreateNewObject("Name") };
		nameObject->GetTransform()->SetWorldPosition(leftPos);

		auto nameRender = nameObject->AddComponent<RenderComponent>();
		auto nameText = nameObject->AddComponent<TextComponent>();
		nameText->SetFont(pSmallFont);
		nameText->SetText(pair.second);
		if (pair == entry)
		{
			nameText->SetColor(253.f, 255.f, 32.f);
		}
		else
		{
			nameText->SetColor(255.f, 255.f, 255.f);
		}

		const auto scoreObject{ m_pScreen->CreateNewObject("Score") };
		scoreObject->GetTransform()->SetWorldPosition(rightPos);

		auto scoreRender = scoreObject->AddComponent<RenderComponent>();
		auto scoreText = scoreObject->AddComponent<TextComponent>();
		scoreText->SetFont(pSmallFont);
		scoreText->SetText(std::to_string(pair.first));
		if (pair == entry)
		{
			scoreText->SetColor(253.f, 255.f, 32.f);
		}
		else
		{
			scoreText->SetColor(255.f, 255.f, 255.f);
		}

		leftPos.y += step;
		rightPos.y += step;
	}

}

void D2D::HighscoresState::ReadFromFile(const std::string& fileName, std::vector<std::pair<int, std::string>>& entries)
{
	std::ifstream file;
	file.open(fileName);
	std::string line;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::regex pattern("<\"(\\d+)\", \"([A-Z]+)\">");

			std::smatch matches;
			if (std::regex_search(line, matches, pattern)) {
				if (matches.size() >= 3) {
					int value1 = std::stoi(matches[1].str());
					std::string value2 = matches[2].str();

					std::pair<int, std::string> entry{ std::make_pair(value1, value2) };

					entries.emplace_back(entry);

				}
			}
		}
	}
}

void D2D::HighscoresState::WriteToFile(const std::string& fileName, std::vector<std::pair<int, std::string>>& entries)
{
	std::ofstream file;
	file.open(fileName);
	std::string line;

	for (auto& pair : entries)
	{
		line = "<\"" + std::to_string(pair.first) + "\", \"" + pair.second + "\">\n";

		file << line;
	}

	file.close();
}

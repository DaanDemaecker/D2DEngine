#include "pch.h"
#include "HighScoreStates.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "FunctionCommand.h"
#include "TextComponent.h"
#include "HighScoreScreenComponent.h"
#include "GameData.h"

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

	if (m_pSelector != nullptr && m_Selected < m_pLetters.size())
	{
		m_pSelector->SetActive(true);
		m_pSelector->SetParent(m_pLetters[m_Selected]->GetOwner(), false);
	}
	
}

void D2D::InputState::VerticalScroll(int direction)
{
	if (!m_Active || m_Selected >= m_pLetters.size())
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

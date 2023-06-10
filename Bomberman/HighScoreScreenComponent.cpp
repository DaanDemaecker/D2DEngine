#include "pch.h"
#include "HighScoreScreenComponent.h"
#include "GameData.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "Transform.h"
#include "Texture2D.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "glm/glm.hpp"

#include "SDL.h"

extern SDL_Window* g_window;

D2D::HighScoreScreenComponent::~HighScoreScreenComponent()
{

}

void D2D::HighScoreScreenComponent::Initialize(GameObject* pInputWindow, GameObject* pHighscoresWindow)
{
	m_pInputState = std::make_unique<InputState>();
	m_pHighscoresState = std::make_unique<HighscoresState>();


	SetupInputState(pInputWindow);
	m_pHighscoresState->SetVariables(pHighscoresWindow);

	SetState(m_pInputState.get());
}

void D2D::HighScoreScreenComponent::OnSceneLoad()
{
	SetState(m_pInputState.get());

	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetText(std::to_string(GameData::GetInstance().GetScore()));
	}

	ServiceLocator::GetSoundSystem().Play(9, 128, -1);
}

void D2D::HighScoreScreenComponent::OnSceneUnload()
{
	ServiceLocator::GetSoundSystem().StopMusic();
	//InputManager::GetInstance().RemoveCommands(SceneManager::GetInstance().GetActiveScene()->GetName());
}

void D2D::HighScoreScreenComponent::Update()
{
	if (m_pState != nullptr)
	{
		m_pState->Update();

		m_pState->ChangeState(this);
	}
}

void D2D::HighScoreScreenComponent::SetState(HighScoreStates* pNewState)
{
	if (pNewState != nullptr)
	{
		if (m_pState != nullptr)
		{
			m_pState->OnStateLeave();
		}

		m_pState = pNewState;

		m_pState->OnStateEnter();
	}
}

void D2D::HighScoreScreenComponent::SetupInputState(GameObject* pInputWindow)
{
	auto& pResourceManager = ResourceManager::GetInstance();
	const auto pBigFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 100) };
	const auto pSmallFont{ pResourceManager.LoadFont("Fonts/Minecraft.ttf", 30) };
	const auto upArrowTexture{ pResourceManager.LoadTexture("sprites/UpArrow.png") };
	const auto downArrowTexture{ pResourceManager.LoadTexture("sprites/DownArrow.png") };
	const auto selectorTexture{ pResourceManager.LoadTexture("sprites/HorizontalSelector.png") };

	int windowWidth{}, windowHeight{};
	SDL_GetWindowSize(g_window, &windowWidth, &windowHeight);

	constexpr float difference{75};
	glm::vec2 textPos{static_cast<float>(windowWidth)/2 - 1.5f * difference, static_cast<float>(windowHeight)/2};
	glm::vec2 lineDifference{ 10, 80 };


	const auto letter1Component{ pInputWindow->CreateNewObject("Letter 1") };
	letter1Component->GetTransform()->SetWorldPosition(textPos);

	auto letter1Render{ letter1Component->AddComponent<RenderComponent>() };
	auto letter1Text{ letter1Component->AddComponent<TextComponent>() };
	letter1Text->SetFont(pBigFont);
	letter1Text->SetColor(255.f, 255.f, 255.f);
	letter1Text->SetText("A");

	AddArrows(letter1Component, upArrowTexture, downArrowTexture);

	textPos.x += difference;

	const auto letter2Component{pInputWindow->CreateNewObject("Letter 2")};
	letter2Component->GetTransform()->SetWorldPosition(textPos);

	auto letter2Render{ letter2Component->AddComponent<RenderComponent>() };
	auto letter2Text{ letter2Component->AddComponent<TextComponent>() };
	letter2Text->SetFont(pBigFont);
	letter2Text->SetColor(255.f, 255.f, 255.f);
	letter2Text->SetText("A");

	AddArrows(letter2Component, upArrowTexture, downArrowTexture);


	textPos.x += difference;

	const auto letter3Component{ pInputWindow->CreateNewObject("Letter 3") };
	letter3Component->GetTransform()->SetWorldPosition(textPos);

	auto letter3Render{ letter3Component->AddComponent<RenderComponent>() };
	auto letter3Text{ letter3Component->AddComponent<TextComponent>() };
	letter3Text->SetFont(pBigFont);
	letter3Text->SetColor(255.f, 255.f, 255.f);
	letter3Text->SetText("A");

	AddArrows(letter3Component, upArrowTexture, downArrowTexture);
	
	textPos.x += difference;
	textPos.y += 20;

	const auto doneComponent{pInputWindow->CreateNewObject("Done")};
	doneComponent->GetTransform()->SetWorldPosition(textPos);

	auto doneRenderer{ doneComponent->AddComponent<RenderComponent>() };
	auto doneText{ doneComponent->AddComponent<TextComponent>() };
	doneText->SetFont(pSmallFont);
	doneText->SetColor(255.f, 255.f, 255.f);
	doneText->SetText("DONE");


	auto scoreObject{ pInputWindow->CreateNewObject("Score Object") };
	scoreObject->GetTransform()->SetWorldPosition(static_cast<float>(windowWidth)/2 - 150, static_cast<float>(windowHeight) - 75);

	auto scoreRenderer{ scoreObject->AddComponent<RenderComponent>() };
	auto scoreRendererText{ scoreObject->AddComponent<TextComponent>() };
	scoreRendererText->SetFont(pSmallFont);
	scoreRendererText->SetColor(255.f, 255.f, 255.f);
	scoreRendererText->SetText("Your score: ");


	auto scoreText{ scoreObject->CreateNewObject("Score Text") };
	scoreText->GetTransform()->SetLocalPosition(200, 0);

	scoreText->AddComponent<RenderComponent>();
	m_pTextComponent = scoreText->AddComponent<TextComponent>().get();
	m_pTextComponent->SetFont(pSmallFont);
	m_pTextComponent->SetColor(255.f, 255.f, 255.f);
	m_pTextComponent->SetText("test");

	m_pInputState->SetVariables(pInputWindow, letter1Text.get(), letter2Text.get(), letter3Text.get(), doneText.get());
}

void D2D::HighScoreScreenComponent::AddArrows(GameObject* pLetter, std::shared_ptr<Texture2D> upArrow, std::shared_ptr<Texture2D> downArrow)
{
	glm::vec2 upArrowdifference{ 17, -35 };
	glm::vec2 downArrowDifference{ 17, 90 };

	const auto upArrowObject1{ pLetter->CreateNewObject("Up Arrow") };
	upArrowObject1->GetTransform()->SetLocalPosition(upArrowdifference);

	auto upArrow1Render{ upArrowObject1->AddComponent<RenderComponent>() };
	upArrow1Render->SetTexture(upArrow);

	const auto downArrowObject1{ pLetter->CreateNewObject("Down Arrow") };
	downArrowObject1->GetTransform()->SetLocalPosition(downArrowDifference);

	auto downArrow1Render{ downArrowObject1->AddComponent<RenderComponent>() };
	downArrow1Render->SetTexture(downArrow);
}

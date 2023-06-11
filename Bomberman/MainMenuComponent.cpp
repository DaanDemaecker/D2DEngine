#include "pch.h"
#include "MainMenuComponent.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "GameData.h"
#include <iostream>

void D2D::MainMenuComponent::OnSceneLoad()
{
	ServiceLocator::GetSoundSystem().Play(5, 128, -1);
}

void D2D::MainMenuComponent::OnSceneUnload()
{
	ServiceLocator::GetSoundSystem().StopMusic();
}

void D2D::MainMenuComponent::SinglePlayerButton()
{
	GameData::GetInstance().SetGameMode(GameMode::SinglePlayer);
	D2D::SceneManager::GetInstance().NextScene();
}                                                     
 
void D2D::MainMenuComponent::CoopButton()
{
	GameData::GetInstance().SetGameMode(GameMode::Coop);
	D2D::SceneManager::GetInstance().NextScene();
}

void D2D::MainMenuComponent::VersusButton()
{
	GameData::GetInstance().SetGameMode(GameMode::Versus);
	D2D::SceneManager::GetInstance().NextScene();
}
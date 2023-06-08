#include "pch.h"
#include "MainMenuComponent.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ServiceLocator.h"
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
	D2D::SceneManager::GetInstance().NextScene();
}                                                     
 
void D2D::MainMenuComponent::CoopButton()
{
	std::cout << "CoopButton\n";
}

void D2D::MainMenuComponent::VersusButton()
{
	std::cout << "VersusButton\n";
}
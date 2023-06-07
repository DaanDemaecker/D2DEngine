#include "pch.h"
#include "MainMenuComponent.h"
#include "SceneManager.h"
#include "InputManager.h"
#include <iostream>

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
#include "pch.h"
#include "MainMenuComponent.h"
#include "SceneManager.h"
#include "BombermanScene.h"
#include "InputManager.h"
#include <iostream>

void D2D::MainMenuComponent::SinglePlayerButton()
{
	auto& bombermanScene = D2D::SceneManager::GetInstance().CreateScene("Bomberman");
	D2D::LoadBombermanScene(bombermanScene);
	
	D2D::InputManager::GetInstance().RemoveCommands("StartScreen");
	D2D::SceneManager::GetInstance().DeleteScene("StartScreen");
}                                                     
 
void D2D::MainMenuComponent::CoopButton()
{
	std::cout << "CoopButton\n";
}

void D2D::MainMenuComponent::VersusButton()
{
	std::cout << "VersusButton\n";
}
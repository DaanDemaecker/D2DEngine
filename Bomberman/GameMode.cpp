#include "pch.h"
#include "GameMode.h"
#include "ServiceLocator.h"

void D2D::GameMode::OnSceneLoad()
{
	ServiceLocator::GetSoundSystem().Play(0, 128, -1);
}

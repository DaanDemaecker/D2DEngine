#include "pch.h"
#include "ToggleSoundCommand.h"
#include "ServiceLocator.h"

void D2D::ToggleSoundCommand::Execute()
{
	ServiceLocator::GetSoundSystem().ToggleMute();
}

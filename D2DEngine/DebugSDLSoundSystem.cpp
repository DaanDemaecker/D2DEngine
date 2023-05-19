#include "DebugSDLSoundSystem.h"
#include "SDLSoundSystem.h"
#include <iostream>

D2D::DebugSDLSoundSystem::DebugSDLSoundSystem()
{
	m_pSDLSoundSystem = std::make_unique<SDLSoundSystem>();
}

void D2D::DebugSDLSoundSystem::Play(unsigned short id, int string, int loops)
{
	m_pSDLSoundSystem->Play(id, string, loops);

	std::cout << "Playing sound with id: " << id << std::endl;
}

void D2D::DebugSDLSoundSystem::ReadSoundSheet(const std::string& path)
{
	m_pSDLSoundSystem->ReadSoundSheet(path);

	std::cout << "Reading in soundsheet: " << path << std::endl;
}

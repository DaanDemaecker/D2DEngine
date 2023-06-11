#include "DebugSDLSoundSystem.h"
#include "SDLSoundSystem.h"
#include <iostream>

D2D::DebugSDLSoundSystem::DebugSDLSoundSystem()
{
	m_pSDLSoundSystem = std::make_unique<SDLSoundSystem>();
}

void D2D::DebugSDLSoundSystem::Play(unsigned short id, int volume, int loops)
{
	m_pSDLSoundSystem->Play(id, volume, loops);

	std::cout << "Playing sound with id: " << id << std::endl;
}

void D2D::DebugSDLSoundSystem::ReadSoundSheet(const std::string& path)
{
	m_pSDLSoundSystem->ReadSoundSheet(path);

	std::cout << "Reading in soundsheet: " << path << std::endl;
}

void D2D::DebugSDLSoundSystem::StopMusic()
{
	m_pSDLSoundSystem->StopMusic();

	std::cout << "Stopped music \n";
}

void D2D::DebugSDLSoundSystem::SetVolume(float volume)
{
	m_pSDLSoundSystem->SetVolume(volume);

	std::cout << "Setting volume to " << volume << std::endl;
}

void D2D::DebugSDLSoundSystem::ToggleMute()
{
	m_pSDLSoundSystem->ToggleMute();

	std::cout << "Toggling volume " << std::endl;
}

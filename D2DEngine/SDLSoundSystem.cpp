#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include "SDL.h"
#include "ResourceManager.h"

#include "ResourceManager.h"

#include <sstream>
#include <iostream>


D2D::SDLSoundSystem::SDLSoundSystem()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		// Handle the error
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0) {
		std::cout << "Failed to open audio device: " << Mix_GetError() << std::endl;
		// Handle the error
	}

	// Load audio file
	std::stringstream ss{};
	ss << ResourceManager::GetInstance().GetPath() << "Sound/SoundEffects/Explosion.wav";

	m_pTest = Mix_LoadWAV(ss.str().c_str());
	if (!m_pTest)
	{
		printf("Error loading sound: %s\n", Mix_GetError());
		return;
	}

}

D2D::SDLSoundSystem::~SDLSoundSystem()
{
	Mix_FreeChunk(m_pTest);
	Mix_Quit();
}

void D2D::SDLSoundSystem::Play()
{
	std::cout << "hellow \n";

	// Play audio
	Mix_Volume(0, 128);


	const int channel = Mix_PlayChannel(-1, m_pTest, 0);
	if (channel == -1)
	{
		std::cout << "Failed to find open channel: " << channel << "\n";
	}

	

}

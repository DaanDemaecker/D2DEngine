#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include "SDL.h"
#include "ResourceManager.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>

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

	m_Thread = std::jthread(&SDLSoundSystem::Run, this);
}

D2D::SDLSoundSystem::~SDLSoundSystem()
{
	m_IsRunning = false;
	m_ConditionVariable.notify_one();
	m_Thread.join();

	ClearSoundChunks();
	Mix_Quit();
}

void D2D::SDLSoundSystem::Play(unsigned short id, int volume)
{
	std::lock_guard<std::mutex> lock{ m_Mutex };

	m_Queue.push_back(std::pair<unsigned short, int>{id, volume});

	m_ConditionVariable.notify_one();
}

void D2D::SDLSoundSystem::ReadSoundSheet(const std::string& filePath)
{
	ClearSoundChunks();

	std::stringstream resourcesFilePath{};
	resourcesFilePath << ResourceManager::GetInstance().GetPath();

	// Load audio file
	std::stringstream ss{};
	ss << resourcesFilePath.str() << filePath;

	std::ifstream file;
	file.open(ss.str().c_str());
	std::string line;

	if (file.is_open())
	{
		std::getline(file, line, '\"');
		std::getline(file, line, '\"');

		std::stringstream soundeffectsFilePath{};
		soundeffectsFilePath << resourcesFilePath.str() << line;

		
		std::regex pattern("<\"(\\d+)\" = \"(.+\\.wav)\">");
		while (std::getline(file, line))
		{
			unsigned short id{};
			std::string soundEffectName{};

			
			std::smatch matches;

			// Try to match the pattern
			if (std::regex_match(line, matches, pattern))
			{
				// Extract the values from the match results
				id = static_cast<unsigned short>(std::stoi(matches[1].str()));
				soundEffectName = matches[2].str();

				m_pSoundChunks[id] = Mix_LoadWAV((soundeffectsFilePath.str() + soundEffectName).c_str());
				if (!m_pSoundChunks[id])
				{
					std::cout << "failed to open sound effect";
				}
			}
		}
	}
}

void D2D::SDLSoundSystem::ClearSoundChunks()
{
	for (auto& pair : m_pSoundChunks)
	{
		Mix_FreeChunk(pair.second);
	}
}

void D2D::SDLSoundSystem::Run()
{
	while (m_IsRunning)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		if (m_Queue.size() > 0)
		{
			PlaySound(m_Queue[0].first, m_Queue[0].second);
			m_Queue.pop_front();
		}
		m_ConditionVariable.wait(lock);
	}
}

void D2D::SDLSoundSystem::PlaySound(unsigned short id, int volume)
{
	if (m_pSoundChunks.count(id) <= 0)
	{
		std::cout << "Failed to find sound chunk: " << id << "\n";
		return;
	}

	const int channel = Mix_GroupAvailable(-1);
	if (channel == -1)
	{
		std::cout << "Failed to find open channel: " << channel << "\n";
	}
	else
	{
		Mix_Volume(0, volume);
		Mix_PlayChannel(-1, m_pSoundChunks[id], 0);
	}
}

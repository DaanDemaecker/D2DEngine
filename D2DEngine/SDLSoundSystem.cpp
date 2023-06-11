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

void D2D::SDLSoundSystem::Play(unsigned short id, int volume, int loops)
{
	std::unique_lock<std::mutex> lock{ m_Mutex };

	m_Queue.push_back(std::make_tuple(id, static_cast<int>(volume * m_ActualVolume), loops));

	m_ConditionVariable.notify_one();
}

void D2D::SDLSoundSystem::ToggleMute()
{
	m_IsMuted = !m_IsMuted;
	
	if (m_IsMuted)
	{
		Mix_VolumeMusic(0);
		m_ActualVolume = 0;
	}
	else
	{
		Mix_VolumeMusic(static_cast<int>(128 * m_Volume));
		m_ActualVolume = m_Volume;
	}
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

		
		std::regex wavPattern("<\"(\\d+)\" = \"(.+\\.wav)\">");
		std::regex mp3Pattern("<\"(\\d+)\" = \"(.+\\.mp3)\">");
		while (std::getline(file, line))
		{
			unsigned short id{};
			std::string soundEffectName{};

			
			std::smatch matches;

			// Try to match the pattern
			if (std::regex_match(line, matches, wavPattern))
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
			else if (std::regex_match(line, matches, mp3Pattern))
			{
				// Extract the values from the match results
				id = static_cast<unsigned short>(std::stoi(matches[1].str()));
				soundEffectName = matches[2].str();

				m_pSoundMusic[id] = Mix_LoadMUS((soundeffectsFilePath.str() + soundEffectName).c_str());
				if (!m_pSoundMusic[id])
				{
					std::cout << "failed to open mp3 file";
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

	for (auto& pair : m_pSoundMusic)
	{
		Mix_FreeMusic(pair.second);
	}
}

void D2D::SDLSoundSystem::Run()
{
	while (m_IsRunning)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		m_ConditionVariable.wait(lock);

		while (!m_Queue.empty())
		{
			auto queueEntry = m_Queue[0];
			m_Queue.pop_front();

			lock.unlock();

			PlaySound(queueEntry);

			lock.lock();
		}
	}
}

void D2D::SDLSoundSystem::StopMusic()
{
	Mix_HaltMusic();
}

void D2D::SDLSoundSystem::PlaySound(const std::tuple<unsigned short, int, int>& queueEntry)
{
	if (m_pSoundChunks.contains(std::get<0>(queueEntry)))
	{
		const int channel = Mix_GroupAvailable(-1);
		if (channel == -1)
		{
			std::cout << "Failed to find open channel: " << channel << "\n";
		}
		else
		{
			Mix_Volume(channel, std::get<1>(queueEntry));
			Mix_PlayChannel(-1, m_pSoundChunks[std::get<0>(queueEntry)], std::get<2>(queueEntry));
		}
	}
	else if (m_pSoundMusic.contains(std::get<0>(queueEntry)))
	{
		Mix_VolumeMusic(std::get<1>(queueEntry));
		Mix_PlayMusic(m_pSoundMusic[std::get<0>(queueEntry)], std::get<2>(queueEntry));
	}
	else
	{
		std::cout << "Failed to find sound chunk: " << std::get<0>(queueEntry) << "\n";
		return;
	}

	
}

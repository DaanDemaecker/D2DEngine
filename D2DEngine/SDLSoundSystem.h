#pragma once
#include "SoundSystem.h"
#include <map>
#include <deque>
#include <thread>
#include <mutex>

struct Mix_Chunk;

namespace D2D
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem();

		virtual void Play(unsigned short id, int voume) override;

		virtual void ReadSoundSheet(const std::string& filePath) override;

		void Run();

	private:
		std::map<unsigned short, Mix_Chunk*> m_pSoundChunks{};

		std::deque<std::pair<unsigned short, int >> m_Queue{};

		std::jthread m_Thread{};
		std::condition_variable m_ConditionVariable{};

		bool m_IsRunning{ true };

		std::mutex m_Mutex{};

		void ClearSoundChunks();

		void PlaySound(unsigned short id, int volume);
	};
}

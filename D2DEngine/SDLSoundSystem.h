#pragma once
#include "SoundSystem.h"
#include <map>
#include <deque>
#include <thread>
#include <mutex>

struct Mix_Chunk;
struct _Mix_Music;

namespace D2D
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem();

		virtual void Play(unsigned short id, int voume, int loops = 0) override;

		virtual void SetVolume(float volume) override { m_Volume = volume; if (!m_IsMuted) { m_ActualVolume = volume; } }

		virtual void ToggleMute() override;

		virtual void ReadSoundSheet(const std::string& filePath) override;

		void Run();

		virtual void StopMusic();

	private:
		float m_Volume{ 1.f };
		float m_ActualVolume{ 1.f };

		bool m_IsMuted{ false };

		std::map<unsigned short, Mix_Chunk*> m_pSoundChunks{};
		std::map<unsigned short, _Mix_Music*> m_pSoundMusic{};

		std::deque<std::tuple<unsigned short, int, int >> m_Queue{};


		std::jthread m_Thread{};
		std::condition_variable m_ConditionVariable{};

		bool m_IsRunning{ true };

		std::mutex m_Mutex{};

		void ClearSoundChunks();

		void PlaySound(const std::tuple<unsigned short, int, int>& queueEntry);
	};
}

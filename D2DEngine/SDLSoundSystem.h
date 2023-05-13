#pragma once
#include "SoundSystem.h"
#include <map>

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

	private:
		std::map<unsigned short, Mix_Chunk*> m_pSoundChunks{};

		void ClearSoundChunks();
	};
}

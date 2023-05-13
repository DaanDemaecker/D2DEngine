#pragma once
#include "SoundSystem.h"

struct Mix_Chunk;

namespace D2D
{


	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem();

		virtual void Play() override;

	private:
		Mix_Chunk* m_pTest;
	};
}

#pragma once
#include "SoundSystem.h"


namespace D2D
{
	class SDLSoundSystem;

	class DebugSDLSoundSystem final : public SoundSystem
	{
	public:
		DebugSDLSoundSystem();
		virtual ~DebugSDLSoundSystem() override = default;

		virtual void Play(unsigned short id, int volume, int loops) override;

		virtual void ReadSoundSheet(const std::string& path) override;
	private:
		std::unique_ptr<SDLSoundSystem> m_pSDLSoundSystem{};
	};
}

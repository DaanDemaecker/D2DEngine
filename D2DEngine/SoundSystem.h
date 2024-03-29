#pragma once
#include <iostream>

namespace D2D
{
	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem() = default;

		SoundSystem(SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;

		SoundSystem& operator=(SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;

		virtual void Play(unsigned short id, int voume, int loops = 0) = 0;

		virtual void StopMusic() = 0;

		virtual void ToggleMute() = 0;

		virtual void SetVolume(float volume) = 0;

		virtual void ReadSoundSheet(const std::string& filePath) = 0;

	};

	class DefaultSoundSystem final : public SoundSystem
	{
	public:
		DefaultSoundSystem() = default;
		virtual ~DefaultSoundSystem() override = default;

		virtual void Play(unsigned short , int, int = 0) override {}

		virtual void StopMusic() override {}

		virtual void ToggleMute() override {}

		virtual void SetVolume(float) override {}

		virtual void ReadSoundSheet(const std::string&) override {}

	};



}

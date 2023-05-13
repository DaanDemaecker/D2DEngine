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

		virtual void Play(unsigned short id, int voume) = 0;

		virtual void ReadSoundSheet(const std::string& filePath) = 0;

	};

	class DefaultSoundSystem final : public SoundSystem
	{
	public:
		DefaultSoundSystem() = default;
		virtual ~DefaultSoundSystem() override = default;

		virtual void Play(unsigned short, int) override {}

		virtual void ReadSoundSheet(const std::string&) override {}

	};



}

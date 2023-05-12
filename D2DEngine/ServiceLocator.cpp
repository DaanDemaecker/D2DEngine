#include "ServiceLocator.h"

namespace D2D
{
    std::unique_ptr<DefaultSoundSystem> ServiceLocator::m_DefaultSoundSystemInstance{ std::make_unique<DefaultSoundSystem>() };
    std::unique_ptr<SoundSystem> ServiceLocator::m_pSoundSystemInstance{ nullptr };


    void ServiceLocator::register_sound_system(std::unique_ptr<SoundSystem> soundSystem)
    {
        if (soundSystem != nullptr)
        {
            m_pSoundSystemInstance = std::move(soundSystem);
        }
    }

    SoundSystem& ServiceLocator::GetSoundSystem()
    {
        return m_pSoundSystemInstance.get() == nullptr ? *m_DefaultSoundSystemInstance.get() : *m_pSoundSystemInstance.get();
    }
}
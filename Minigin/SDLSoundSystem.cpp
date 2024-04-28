#include "SDLSoundSystem.h"

#include <cassert>
#include <SDL_mixer.h>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <SDL_mixer.h>
#include <thread>
#include <vector>

namespace dae
{
	class SDLSoundSystem::SDLSoundSystemImpl
	{
	public:
        explicit SDLSoundSystemImpl();
        ~SDLSoundSystemImpl();

        SoundID RegisterSound(SoundType type, const std::string& filePath);
        void PlaySound(SoundType type, SoundID id, int volume);

        void RunThread();

	private:
        std::vector<Mix_Chunk*> m_SFX{};
        std::vector<Mix_Music*> m_Music{};

        std::queue<SoundRequest> m_SoundRequests{};

        std::jthread m_Thread{};
        std::mutex m_Mutex{};
        std::condition_variable m_ConditionVar{};


        bool m_KillThread{ false };
	};

    /////////////////////////////////////
    // SDLSoundSystem Implementation
    /////////////////////////////////////

	SDLSoundSystem::SDLSoundSystemImpl::SDLSoundSystemImpl()
	{
        Mix_Init(MIX_INIT_MP3);
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
        {
            throw SoundInitializeFailedException{};
        }

        m_Thread = std::jthread([this] { RunThread(); });
	}

	SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
	{
        m_KillThread = true;
        m_ConditionVar.notify_all();

        for (auto& chunk : m_SFX)
        {
            Mix_FreeChunk(chunk);
            chunk = nullptr;
        }

        for (auto& music : m_Music)
        {
            Mix_FreeMusic(music);
            music = nullptr;
        }

        Mix_CloseAudio();
        Mix_Quit();
	}

	SoundSystem::SoundID SDLSoundSystem::SDLSoundSystemImpl::RegisterSound(SoundType type, const std::string& filePath)
	{
        std::lock_guard lock{ m_Mutex };
        switch (type)
        {
        case SoundType::sfx:
        {
            Mix_Chunk* chunk{ Mix_LoadWAV(filePath.c_str()) };
            if (!chunk) throw SoundLoadFailedException{};

            m_SFX.emplace_back(chunk);
            return m_SFX.size() - 1;
        }

        case SoundType::music:
        {
            Mix_Music* music{ Mix_LoadMUS(filePath.c_str()) };
            if (!music) throw SoundLoadFailedException{};

            m_Music.emplace_back(music);
            return m_Music.size() - 1;
        }
        }

        throw SoundLoadFailedException{};

	}

	void SDLSoundSystem::SDLSoundSystemImpl::PlaySound(SoundType type, SoundID id, int volume)
	{
        std::lock_guard lock(m_Mutex);
        m_SoundRequests.push(SoundRequest{ type, id, volume });
        m_ConditionVar.notify_all();
	}

	void SDLSoundSystem::SDLSoundSystemImpl::RunThread()
	{
        while (!m_KillThread)
        {
            std::unique_lock lock(m_Mutex);
            m_ConditionVar.wait(lock);

            while (!m_SoundRequests.empty())
            {
                const SoundRequest& currentRequest{ m_SoundRequests.front() };

                switch (currentRequest.type)
                {
                case SoundType::sfx:
                    Mix_Volume(-1, currentRequest.volume);
                    Mix_PlayChannel(-1, m_SFX.at(currentRequest.id), 0);
                    break;

                case SoundType::music:
                    Mix_VolumeMusic(currentRequest.volume);
                    Mix_PlayMusic(m_Music.at(currentRequest.id), -1);
                    break;
                }

                m_SoundRequests.pop();
            }
        }
	}
}

/////////////////////////////////////
// Pimpl Forwards
/////////////////////////////////////

dae::SDLSoundSystem::SDLSoundSystem()
	: m_pImpl{ std::make_unique<SDLSoundSystemImpl>() }
{
}

dae::SDLSoundSystem::~SDLSoundSystem() = default; // Defaulted in .cpp so type for uniqueptr is defined

dae::SoundSystem::SoundID dae::SDLSoundSystem::RegisterSound(SoundType type, const std::string& filePath)
{
    return m_pImpl->RegisterSound(type, filePath);
}

void dae::SDLSoundSystem::PlaySound(SoundType type, SoundID id, int volume)
{
    m_pImpl->PlaySound(type, id, volume);
}

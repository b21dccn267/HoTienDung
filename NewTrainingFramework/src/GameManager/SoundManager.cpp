#include "SoundManager.h"
#include "../../../Include/SDL2/SDL.h"
#include "../../../Include/SDL2/SDL_mixer.h"
#include <cstdio>

SoundManager* SoundManager::instance = nullptr;

void SoundManager::Init()
{
	// Khởi tạo SDL Audio subsystem
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		return;
	}

	// Khởi tạo SDL_mixer với các thông số âm thanh
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		return;
	}

	// Cấp phát 16 channel cho sound effects
	Mix_AllocateChannels(16);

	// Thiết lập volume mặc định
	Mix_VolumeMusic(m_musicVolume);
	Mix_Volume(-1, m_sfxVolume); // -1 = all channels

	printf("SoundManager initialized successfully\n");
}

void SoundManager::LoadMusic(const std::string& key, const char* fileName)
{
	// Kiểm tra xem music đã được load chưa
	if (m_musicMap.find(key) != m_musicMap.end()) {
		return;
	}

	// Load music file
	Mix_Music* music = Mix_LoadMUS(fileName);
	if (!music) {
		return;
	}

	// Lưu vào map
	m_musicMap[key] = music;
}

void SoundManager::LoadSfx(const std::string& key, const char* fileName)
{
	// Kiểm tra xem sound effect đã được load chưa
	if (m_sfxMap.find(key) != m_sfxMap.end()) {
		return;
	}

	// Load sound effect file
	Mix_Chunk* chunk = Mix_LoadWAV(fileName);
	if (!chunk) {
		return;
	}

	// Lưu vào map
	m_sfxMap[key] = chunk;
}

void SoundManager::PlayMusic(const std::string& key, int loops)
{
	// Nếu sound bị tắt thì không play
	if (!m_soundEnabled) {
		return;
	}

	// Tìm music trong map
	auto it = m_musicMap.find(key);
	if (it == m_musicMap.end()) {
		return;
	}

	// Stop nhạc hiện tại nếu có
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}

	// Play nhạc mới
	if (Mix_PlayMusic(it->second, loops) == -1) {
		return;
	}

	// Lưu reference đến nhạc hiện tại
	m_currentMusic = it->second;
	m_currentMusicKey = key;
}

void SoundManager::PlaySfx(const std::string& key)
{
	// Nếu sound effects bị tắt thì không play
	if (!m_sfxEnabled) {
		return;
	}

	// Tìm sound effect trong map
	auto it = m_sfxMap.find(key);
	if (it == m_sfxMap.end()) {
		return;
	}

	// Play sound effect trên channel tự do (channel -1)
	int channel = Mix_PlayChannel(-1, it->second, 0);
	//if (channel == -1) {}
}

void SoundManager::StopMusic()
{
	Mix_HaltMusic();
	m_currentMusic = nullptr;
	m_currentMusicKey.clear();
}

void SoundManager::PauseMusic()
{
	if (Mix_PlayingMusic()) {
		Mix_PauseMusic();
	}
}

void SoundManager::ResumeMusic()
{
	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
}

void SoundManager::SetMusicVolume(int volume)
{
	// Đảm bảo volume trong khoảng 0-128
	m_musicVolume = (volume < 0) ? 0 : (volume > 128) ? 128 : volume;
	Mix_VolumeMusic(m_musicVolume);
}

void SoundManager::SetSfxVolume(int volume)
{
	// Đảm bảo volume trong khoảng 0-128
	m_sfxVolume = (volume < 0) ? 0 : (volume > 128) ? 128 : volume;
	Mix_Volume(-1, m_sfxVolume); // Áp dụng cho tất cả channels
}

void SoundManager::SetSoundEnabled(bool enabled)
{
	m_soundEnabled = enabled;

	// Nếu tắt âm thanh và đang có nhạc chạy thì pause
	if (!enabled && Mix_PlayingMusic()) {
		PauseMusic();
	}
	// Nếu bật âm thanh và có nhạc bị pause thì resume
	else if (enabled && Mix_PausedMusic()) {
		ResumeMusic();
	}
}

void SoundManager::SetSfxEnabled(bool enabled)
{
	m_sfxEnabled = enabled;

	// Nếu tắt sound effects thì stop tất cả sound effects đang chạy
	if (!enabled) {
		Mix_HaltChannel(-1); // Stop all channels
	}
}

void SoundManager::Cleanup()
{
	// Stop tất cả âm thanh
	Mix_HaltMusic();
	Mix_HaltChannel(-1);

	// Giải phóng tất cả music
	for (auto& pair : m_musicMap) {
		if (pair.second) {
			Mix_FreeMusic(pair.second);
		}
	}
	m_musicMap.clear();

	// Giải phóng tất cả sound effects
	for (auto& pair : m_sfxMap) {
		if (pair.second) {
			Mix_FreeChunk(pair.second);
		}
	}
	m_sfxMap.clear();

	// Đóng SDL_mixer
	Mix_CloseAudio();

	// Cleanup SDL
	SDL_Quit();
}
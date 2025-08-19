#include "SoundManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cstdio>
#include <fstream>
#include <iostream>

SoundManager* SoundManager::instance = nullptr;

void SoundManager::Init()
{
	// Khởi tạo SDL Audio subsystem
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("SDL_Init Audio failed: %s\n", SDL_GetError());
		return;
	}

	// Khởi tạo SDL_mixer với các thông số âm thanh
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("Mix_OpenAudio failed: %s\n", Mix_GetError());
		return;
	}

	// Cấp phát 16 channel cho sound effects
	Mix_AllocateChannels(16);

	// Load settings từ file (hoặc sử dụng default nếu không có file)
	LoadSettings();

	// Thiết lập volume
	Mix_VolumeMusic(m_musicVolume);
	Mix_Volume(-1, m_sfxVolume); // -1 = all channels

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
		printf("Failed to load music %s: %s\n", fileName, Mix_GetError());
		return;
	}

	// Lưu vào map
	m_musicMap[key] = music;
	printf("Loaded music: %s\n", key.c_str());
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
		printf("Failed to load SFX %s: %s\n", fileName, Mix_GetError());
		return;
	}

	// Lưu vào map
	m_sfxMap[key] = chunk;
	printf("Loaded SFX: %s\n", key.c_str());
}

void SoundManager::PlayMusic(const std::string& key, int loops)
{
	// Nếu sound bị tắt thì không play
	if (!m_soundEnabled) {
		printf("Music disabled, not playing: %s\n", key.c_str());
		return;
	}

	// Tìm music trong map
	auto it = m_musicMap.find(key);
	if (it == m_musicMap.end()) {
		printf("Music not found: %s\n", key.c_str());
		return;
	}

	// Stop nhạc hiện tại nếu có
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}

	// Play nhạc mới
	if (Mix_PlayMusic(it->second, loops) == -1) {
		printf("Failed to play music %s: %s\n", key.c_str(), Mix_GetError());
		return;
	}

	// Lưu reference đến nhạc hiện tại
	m_currentMusic = it->second;
	m_currentMusicKey = key;
	printf("Playing music: %s\n", key.c_str());
}

void SoundManager::PlaySfx(const std::string& key)
{
	// Nếu sound bị tắt thì không play (sfx follows sound setting)
	if (!m_soundEnabled || !m_sfxEnabled) {
		return;
	}

	// Tìm sound effect trong map
	auto it = m_sfxMap.find(key);
	if (it == m_sfxMap.end()) {
		printf("SFX not found: %s\n", key.c_str());
		return;
	}

	// Play sound effect trên channel tự do (channel -1)
	int channel = Mix_PlayChannel(-1, it->second, 0);
	if (channel == -1) {
		printf("Failed to play SFX %s: %s\n", key.c_str(), Mix_GetError());
	}
}

void SoundManager::StopMusic()
{
	Mix_HaltMusic();
	m_currentMusic = nullptr;
	m_currentMusicKey.clear();
	printf("Music stopped\n");
}

void SoundManager::PauseMusic()
{
	if (Mix_PlayingMusic()) {
		Mix_PauseMusic();
		printf("Music paused\n");
	}
}

void SoundManager::ResumeMusic()
{
	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
		printf("Music resumed\n");
	}
}

void SoundManager::SetMusicVolume(int volume)
{
	// Volume range: 0-100, nhưng SDL_mixer cần 0-128
	m_musicVolume = (volume < 0) ? 0 : (volume > 100) ? 100 : volume;

	// Convert 0-100 to 0-128 for SDL_mixer
	int sdlVolume = (m_musicVolume * 128) / 100;
	Mix_VolumeMusic(sdlVolume);

	SaveSettings();
	printf("Music volume set to: %d (SDL: %d)\n", m_musicVolume, sdlVolume);
}

void SoundManager::SetSfxVolume(int volume)
{
	// Volume range: 0-100, nhưng SDL_mixer cần 0-128
	m_sfxVolume = (volume < 0) ? 0 : (volume > 100) ? 100 : volume;

	// Convert 0-100 to 0-128 for SDL_mixer
	int sdlVolume = (m_sfxVolume * 128) / 100;
	Mix_Volume(-1, sdlVolume); // Áp dụng cho tất cả channels

	SaveSettings();
	printf("SFX volume set to: %d (SDL: %d)\n", m_sfxVolume, sdlVolume);
}

void SoundManager::SetSoundEnabled(bool enabled)
{
	m_soundEnabled = enabled;
	// Khi tắt sound thì cả music và sfx đều tắt
	m_sfxEnabled = enabled;

	// Nếu tắt âm thanh và đang có nhạc chạy thì halt
	if (!enabled) {
		if (Mix_PlayingMusic()) {
			Mix_HaltMusic();
		}
		// Stop tất cả sound effects
		Mix_HaltChannel(-1);
	}
	// Nếu bật âm thanh và có nhạc hiện tại thì phát lại
	else if (enabled && !m_currentMusicKey.empty()) {
		// Phát lại nhạc hiện tại nếu có
		auto it = m_musicMap.find(m_currentMusicKey);
		if (it != m_musicMap.end()) {
			Mix_PlayMusic(it->second, -1);
		}
	}

	SaveSettings(); // Tự động lưu settings khi thay đổi
}

// Thêm method để dễ dàng switch music giữa các state
void SoundManager::PlayMusicIfEnabled(const std::string& key, int loops)
{
	if (m_soundEnabled) {
		PlayMusic(key, loops);
	}
	else {
		// Chỉ lưu key để có thể phát lại khi bật sound
		m_currentMusicKey = key;
	}
}

void SoundManager::SetSfxEnabled(bool enabled)
{
	// SFX luôn theo trạng thái của Sound chính
	m_sfxEnabled = m_soundEnabled;

	if (!m_sfxEnabled) {
		Mix_HaltChannel(-1); // Stop all channels
	}
}

void SoundManager::SaveSettings()
{
	std::ofstream file("sound_settings.txt");
	if (file.is_open()) {
		file << m_soundEnabled << std::endl;
		file << m_sfxEnabled << std::endl;
		file << m_musicVolume << std::endl;
		file << m_sfxVolume << std::endl;
		file.close();
		printf("Sound settings saved\n");
	}
	else {
		printf("Failed to save sound settings\n");
	}
}

void SoundManager::LoadSettings()
{
	// LUÔN bắt đầu với settings mặc định (sound ON)
	m_soundEnabled = true;
	m_sfxEnabled = true;
	m_musicVolume = 64;
	m_sfxVolume = 64;

	std::ifstream file("sound_settings.txt");
	if (file.is_open()) {
		// CHỈ load nếu file tồn tại VÀ có dữ liệu hợp lệ
		bool tempSound, tempSfx;
		int tempMusicVol, tempSfxVol;

		if (file >> tempSound >> tempSfx >> tempMusicVol >> tempSfxVol) {
			// Chỉ áp dụng settings đã lưu nếu đọc thành công
			m_soundEnabled = tempSound;
			m_sfxEnabled = tempSfx;
			m_musicVolume = (tempMusicVol < 0) ? 0 : (tempMusicVol > 128) ? 128 : tempMusicVol;
			m_sfxVolume = (tempSfxVol < 0) ? 0 : (tempSfxVol > 128) ? 128 : tempSfxVol;

		}
		else {
			printf("Invalid sound settings file, using defaults (SOUND ON)\n");
		}
		file.close();
	}
	else {
		// Sử dụng settings mặc định nếu file không tồn tại (sound ON)
		printf("No sound settings file found, using defaults (SOUND ON)\n");
	}
}

void SoundManager::ResetToDefault()
{
	m_soundEnabled = true;
	m_sfxEnabled = true;
	m_musicVolume = 64;
	m_sfxVolume = 64;

	// Áp dụng settings
	Mix_VolumeMusic(m_musicVolume);
	Mix_Volume(-1, m_sfxVolume);

	SaveSettings();
	printf("Sound settings reset to default (SOUND ON)\n");
}

void SoundManager::Cleanup()
{
	// Save settings trước khi cleanup
	SaveSettings();

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

	// Reset current music info
	m_currentMusic = nullptr;
	m_currentMusicKey.clear();

	// Đóng SDL_mixer
	Mix_CloseAudio();

	// Cleanup SDL
	SDL_Quit();
}
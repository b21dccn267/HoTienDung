#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

class SoundManager
{
public:
	SoundManager(const SoundManager& instance) = delete;
	static SoundManager* instance;
	static SoundManager* GetInstance() {
		if (!instance)
		{
			instance = new SoundManager();
		}
		return instance;
	}
	static void DestroyInstance() {
		delete instance;
		instance = nullptr;
	}

	void Init();

	// Load âm thanh từ file và lưu với key
	void LoadMusic(const std::string& key, const char* fileName);
	void LoadSfx(const std::string& key, const char* fileName);

	// Play âm thanh bằng key
	void PlayMusic(const std::string& key, int loops = -1); 
	void PlayMusicIfEnabled(const std::string& key, int loops = -1);
	void PlaySfx(const std::string& key);

	// Điều khiển âm thanh
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();

	// Điều khiển volume
	void SetMusicVolume(int volume);
	void SetSfxVolume(int volume);   
	int GetMusicVolume() const { return m_musicVolume; }
	int GetSfxVolume() const { return m_sfxVolume; }

	// Điều khiển trạng thái bật/tắt
	void SetSoundEnabled(bool enabled);
	void SetSfxEnabled(bool enabled);
	bool IsSoundEnabled() const { return m_soundEnabled; }
	bool IsSfxEnabled() const { return m_sfxEnabled; }

	// Save/Load settings
	void SaveSettings();
	void LoadSettings();
	void ResetToDefault();  // Reset về trạng thái mặc định

	// Cleanup
	void Cleanup();

private:
	SoundManager() : m_soundEnabled(true), m_sfxEnabled(true),
		m_musicVolume(64), m_sfxVolume(64), m_currentMusic(nullptr) {
	}

	// Containers để lưu âm thanh
	std::map<std::string, Mix_Music*> m_musicMap;
	std::map<std::string, Mix_Chunk*> m_sfxMap;

	// Trạng thái âm thanh
	bool m_soundEnabled;
	bool m_sfxEnabled;
	int m_musicVolume;
	int m_sfxVolume;

	// Track nhạc hiện tại để có thể pause/resume
	Mix_Music* m_currentMusic;
	std::string m_currentMusicKey;
};
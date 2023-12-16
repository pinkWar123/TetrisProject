#pragma once
#include "SFML/Audio.hpp"
#include <vector>
#include<iostream>

enum class SoundEvent
{
	MOVE,
	ROTATE,
	DROP,
	CLEAR,
	GAME_OVER
};

enum class MusicState
{
	PLAY,
	PAUSE,
	STOP
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	static SoundManager &getInstance();
	void playSound(SoundEvent soundEvent);
	void setMusicState(MusicState musicState);
	void ChangeSoundEffectVolum(float volumePercents);
	void ChangeBackGroundMusicVolume(float volumePercents);

private:
	std::vector<sf::Sound> sound;
	sf::Music backgroundMusic;
};

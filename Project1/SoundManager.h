#pragma once
#include "SFML/Audio.hpp"
#include <vector>


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
	static SoundManager& getInstance();
	void playSound(SoundEvent soundEvent);
	void setMusicState(MusicState musicState);
private:
	SoundManager();
	~SoundManager();
	std::vector<sf::Sound> sound;
	sf::Music backgroundMusic;
};


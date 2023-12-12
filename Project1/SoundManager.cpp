#include "SoundManager.h"

SoundManager::SoundManager()
{
	backgroundMusic.openFromFile("Sound/menu.mp3");

	sf::SoundBuffer* moveSound = new sf::SoundBuffer();
	moveSound->loadFromFile("Sound/move.wav");
	sound.push_back(sf::Sound(*moveSound));

	sf::SoundBuffer* rotateSound = new sf::SoundBuffer();
	rotateSound->loadFromFile("Sound/rotate.wav");
	sound.push_back(sf::Sound(*rotateSound));

	sf::SoundBuffer* dropSound = new sf::SoundBuffer();
	dropSound->loadFromFile("Sound/drop.wav");
	sound.push_back(sf::Sound(*dropSound));

	sf::SoundBuffer* clearSound = new sf::SoundBuffer();
	clearSound->loadFromFile("Sound/clear.wav");
	sound.push_back(sf::Sound(*clearSound));

	sf::SoundBuffer* gameOverSound = new sf::SoundBuffer();
	gameOverSound->loadFromFile("Sound/gameOver.wav");
	sound.push_back(sf::Sound(*gameOverSound));
}

SoundManager::~SoundManager()
{
	
}

SoundManager& SoundManager::getInstance()
{
	static SoundManager soundManager;
	return soundManager;
}

void SoundManager::playSound(SoundEvent soundEvent)
{
	int soundIndex = static_cast<int>(soundEvent);
	sound[soundIndex].play();
}
void SoundManager::setMusicState(MusicState musicState)
{
	switch (musicState)
	{
	case(MusicState::PLAY):
		backgroundMusic.play();
		break;
	case(MusicState::PAUSE):
		backgroundMusic.pause();
		break;
	case(MusicState::STOP):
		backgroundMusic.stop();
		break;
	}
}
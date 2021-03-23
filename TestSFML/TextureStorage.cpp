#include "TextureStorage.h"

TextureStorage::TextureStorage()
{
	player.loadFromFile("Textures/player.png");

	background.loadFromFile("Textures/Backgraund.jpg");

	enemy.loadFromFile("Textures/Enemy.png");
	enemy.setSmooth(true);

	explosion.loadFromFile("Textures/explosion.png");
}

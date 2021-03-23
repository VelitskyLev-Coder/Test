#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <list>
#include "TextureStorage.h"
#include <iostream>
#include <algorithm>
#include "EnemySpawner.h"
#include "Explosion.h"
#include "SoundManager.h"
#include "LevelManager.h"
using namespace sf;
using namespace std;
class Game
{
public:
	Game();
	virtual ~Game();
	void mainLoop();
	void eventsProcessing();
	void update();
	void draw();
	void deletingOutOfBord();
	void collisionProcessing();

	const unsigned WIDTH = 600;
	const unsigned HEIGHT = 900;
	TextureStorage textures;

private:


	const string GAME_WINDOW_NAME= "54 must DIE";
	RenderWindow window;

	Sprite background;

	Clock gameClock;

	Player player;

	list<Bullet> bullets;

	list<Enemy> enemys;

	list<Explosion> explosions;

	EnemySpawner enemySpawner;

	SoundManager soundManager;

	LevelManager levelManager;

	int t = 0;
};


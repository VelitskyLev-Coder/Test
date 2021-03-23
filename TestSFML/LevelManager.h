#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "EnemySpawner.h"
#include "SoundManager.h"
#include <iostream>
using namespace std;
using namespace sf;
class LevelManager
{
private:
	Font font;
	Texture back;
	
	Player& player;
	EnemySpawner& enemySpawner;
	Text controlers;
	Text scoreMsg;
	Text LvlMsg;
	Sprite background;
	SoundManager soundManager;
	const int SCORE_TO_LVL = 10000;
public:
	int score;
	int lvl;
	float scoreMult;
	LevelManager(Player& rfPlayer,EnemySpawner& rfEnemySpawner, SoundManager& rfSoundManager);
	void update();
	void draw(RenderWindow& window);
};


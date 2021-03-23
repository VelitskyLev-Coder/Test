#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Bullet.h"
#include <list>
#include "TextureStorage.h"
#include "SFML/Audio.hpp"
using namespace sf;
using namespace std;
class Player
{
public:
	Player(TextureStorage& textures);
	virtual ~Player();

	enum class Actions{LEFT,RIGHT,SHOOT};
	void sendAction(Actions action);
	void update(float dt,list<Bullet>& bullets,Sound& sound);
	void draw(RenderWindow& window);
	Bullet shot();
	FloatRect getGlobalBounds()const;
	float TIME_FOR_REPEAT_SHOT = 0.1f;
private:
	RectangleShape body;

	float velocity;
	float acceleration;
	const float MAX_ACCELERATION = 300.f;
	const float FRICTION_ACCELERATION = 200.f;
	const float MAX_VELOCITY = 200.f;
	const float MAX_LEFT = 0.f;
	const float MAX_RIGHT = 600.f;
	const float DOWN_POSITION = 890.f;
	
	const float SHOT_VELOCITY = 200.f;
	float timeSinceLastShot;
	bool isShot;
};


#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "TextureStorage.h"
using namespace sf;
class Enemy
{
public:
	Enemy(Vector2f position , Vector2f velosity, TextureStorage& textures, float radius);
	virtual ~Enemy();
	void update(float dt);
	void draw(RenderWindow& window);
	Vector2f getPosition() const;
	Vector2f getVelosity() const;
	FloatRect getGlobalBounds()const;
	float getRadius()const;
private:



	Vector2f velosity;

	CircleShape body;

};


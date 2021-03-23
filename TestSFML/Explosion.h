#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "TextureStorage.h" 
#include <iostream>
class Explosion
{
public:
	Explosion(Vector2f position,Texture& texture,float size);
	void update(float dt);
	void draw(RenderWindow& window);
	bool finished()const;
	Explosion& operator =(const Explosion& other);
	float getRadius()const;
	Vector2f getPosition()const;
	bool is_danger()const;
private:
	float const ANIMATION_TIME=1.f;
	
	float currentTime;

	RectangleShape body;
	Texture* texture;

};


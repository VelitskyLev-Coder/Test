#include "Explosion.h"

Explosion::Explosion(Vector2f position, Texture& rtexture,float size)
{
	this->texture = &rtexture;
	currentTime = 0;

	body.setTexture(texture);
	body.setTextureRect(IntRect(0,0,192,192));
	body.setSize(Vector2f(size, size));
	body.setPosition(position - Vector2f(size, size) / 2.f);
}

void Explosion::update(float dt)
{
	currentTime += dt;
	int phase = (int)(currentTime / ANIMATION_TIME * 20.f);
	
	if (phase < 20)
	{
		body.setTextureRect(IntRect(phase % 5 * 192, phase / 5 * 192,  192,  192));
	}
}

void Explosion::draw(RenderWindow& window)
{
	window.draw(body);
	//system("pause");
}

bool Explosion::finished()const
{
	return currentTime > ANIMATION_TIME;
}

Explosion& Explosion::operator=(const Explosion& other)
{
	this->currentTime = other.currentTime;
	this->body = other.body;
	return *this;
}

float Explosion::getRadius() const
{
	return body.getSize().x/2;
}

Vector2f Explosion::getPosition() const
{
	return body.getPosition();
}

bool Explosion::is_danger() const
{
	return currentTime>ANIMATION_TIME*0.3&&currentTime<ANIMATION_TIME*0.4f;
}

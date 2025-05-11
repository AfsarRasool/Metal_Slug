#include "bullet.h"
#include <iostream>
#include"math.h"

Bullet::Bullet()
{
	// Load the texture from a file
	if (!texture.loadFromFile("resources/bullet.png"))
	{
		std::cerr << "Error loading bullet texture" << std::endl;
	}
	// Set the texture to the sprite
	sprite.setTexture(texture);
	// Set the initial position of the bullet
	
}

void Bullet::setposition(Vector2f position)
{
	// Set the position of the bullet
	this->position = position;
	this->position.x = this->position.x+50;
	this->position.y = this->position.y+40;
	sprite.setPosition(position);
}

void Bullet::move()
{
	// Update the position of the bullet
	position += direction;
	sprite.setPosition(position);
}

void Bullet::setDirection(Vector2f target)  // target means mouse position
{
	direction = target - this->position;
	direction = Math::Nomalize_vector(direction);
}

void Bullet::Ready_Bullet(Vector2f Marco_position, Vector2f mouse)
{
	setposition(Marco_position);
	setDirection(mouse);
}

Vector2f Bullet::get_bulletPosition()
{
	return position;
}

FloatRect Bullet::get_global_bounds()
{
	return sprite.getGlobalBounds();
}

void Bullet::draw(RenderWindow& window)
{
	window.draw(sprite);
}


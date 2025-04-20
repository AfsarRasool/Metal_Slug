#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;

class Bullet
{
	private:
	Texture texture;
	Sprite sprite;
	Vector2f position;
	Vector2f direction;

public:
	Bullet();
	void setposition(Vector2f position);
	void draw(RenderWindow& window);
	void move();
	void setDirection(Vector2f mouse);  // Marco is the name of main character
	void Ready_Bullet(Vector2f Marco_position, Vector2f mouse); // target is the cursor Position
	Vector2f get_bulletPosition();
	FloatRect get_global_bounds();
};
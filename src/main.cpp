#include <SFML/Graphics.hpp>
#include <iostream>
#include"bullet.h"
#include"marco.h"
#include"animation.h"

using namespace sf;
using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1360, 768), "SFML works!");
	Texture map_texture;
	map_texture.loadFromFile("resources/level1.png");
	Sprite map_sprite(map_texture);

	float Map_X = static_cast<float>(window.getSize().x) / (map_texture.getSize().x);
	float Map_Y = static_cast<float>(window.getSize().y) / (map_texture.getSize().y);
	map_sprite.setScale(Map_X, Map_Y);

	Texture texture;
	//.............................Initialize......................................................
	Sprite sprite(texture);  

	Marco marco;
	vector < Bullet> bullets;
	Bullet bullet;
	Animation animate;

	sf::Clock clock;
	Vector2f marco_position = sprite.getPosition();
	int increase_oneside = 5;

	// Enemy Sprite
	Texture enemy_texture;
	enemy_texture.loadFromFile("resources/mainC.png");
	

	Sprite enemy_sprite(enemy_texture);
	enemy_sprite.setTextureRect(IntRect(308, 20, 40, 40));
	enemy_sprite.setScale(3, 3);
	int enemy_health = 100;
	enemy_sprite.setPosition(700, 600);

	//..................Variabes...........................................
	bool fire = false; // FIRING
	int fireframe = 0;
	
	Clock fireclock;
	
	  // INHALE
	bool inhale_direction = true;
	Clock inhale_clock;

	bool is_movement = false; // Movement
	Clock Movement_clock;

	bool drink = false;
	Clock drink_clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			

		

			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
			{
				// Adjust the viewport when the window is resized
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
			{
				is_movement = true;
				inhale_direction = true;
				marco_position.x += increase_oneside;
				//sprite.setPosition(marco_position);
				animate.setposition(marco_position);
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
			{
				is_movement = true;
				inhale_direction = false;
				marco_position.x -= increase_oneside;
				animate.setposition(marco_position);
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				if (fireclock.getElapsedTime().asMilliseconds()>50)
				{
				fire = true;
				bullets.push_back(bullet);
				bullets[bullets.size() - 1].Ready_Bullet(sprite.getPosition(), Vector2f(Mouse::getPosition(window)));
				}
			}
			else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::LControl || event.key.code == Keyboard::RControl))
			{
				drink = true;
				
			}
		}

		//calculate the delta time
		sf::Time deltaTime = clock.restart();
		float deltaTimeSeconds = deltaTime.asSeconds();

		//make sure delta time stays within normal bounds, like between one FPS and zero FPS
		deltaTimeSeconds = std::min(deltaTimeSeconds, 1.f);
		deltaTimeSeconds = std::max(deltaTimeSeconds, 0.f);

		//for (int i = 0; i < bullets.size(); i++)
		//{
		//	bullets[i].move();  // it will move in the specified direction
		//	if (bullets[i].get_global_bounds().intersects(enemy_sprite.getGlobalBounds()))
		//	{
		//		enemy_health -= 10;

		//	}
		//}
			for (int i = bullets.size()-1; i>= 0; i--)
		{
			bullets[i].move();  // it will move in the specified direction
			if (bullets[i].get_global_bounds().intersects(enemy_sprite.getGlobalBounds()))
			{
				enemy_health -= 10;
				bullets.erase(bullets.begin() + i);
			}
		}
     
		if (fire)
		{
			animate.Fire_Animatio(sprite, inhale_direction, fireclock,fire);
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Right)|| Keyboard::isKeyPressed(Keyboard::Left)) && is_movement)
		{ 
			
			animate.Forward_Move(sprite, inhale_direction, Movement_clock);
		}
		else if (drink)
		{
			animate.Drink_Animation(sprite, inhale_direction, drink_clock, drink);
		}

		else
		{
			animate.Inhale_Animation(sprite, inhale_direction, inhale_clock);
		}
		//sprite.setPosition(animate.Marco_position.x, animate.Marco_position.y+600);


		sf::FloatRect bounds = sprite.getGlobalBounds(); // assuming your sprite is called bullet

		// Create a rectangle for visualizing the bounds
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(bounds.width, bounds.height));
		rect.setPosition(bounds.left, bounds.top);
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(1.0f);

		
		window.clear();
		window.draw(map_sprite);
		window.draw(sprite);
		

		for (int i = 0; i < bullets.size(); i++)
		{
			
			bullets[i].draw(window);
			
		}
		if (enemy_health>0)
		{
	     	window.draw(enemy_sprite);
		}
		//window.draw(rect);
		window.display();
		
	}

	return 0;
}
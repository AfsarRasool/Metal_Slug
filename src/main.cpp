#include <SFML/Graphics.hpp>
#include <iostream>
#include"bullet.h"
#include"marco.h"
#include"animation.h"
#include"enemy.h"

using namespace sf;
using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1360, 768), "SFML works!");
	//window.setFramerateLimit(60);
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
	
	//vector<Sprite> enemy_sprites;
	//enemy_sprites.push_back(Sprite(enemy_texture));
	//enemy_sprites.push_back(Sprite(enemy_texture));

	//enemy_sprites[0].setTextureRect(IntRect(308, 20, 40, 40));
	//enemy_sprites[1].setTextureRect(IntRect(308, 912, 40, 40));
	//enemy_sprites[0].setScale(3, 3);
	//enemy_sprites[1].setScale(3, 3);
	//enemy_sprites[0].setPosition(800, 615);
	//enemy_sprites[1].setPosition(700, 615);
	//vector<int> enemy_healths;
	//enemy_healths.push_back(100);
	//enemy_healths.push_back(100);

	Enemy e;


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

	Clock Down_shield_clock;
	bool down_stay = false;

	sf::Clock deltaClock;

	while (window.isOpen())
	{
		float deltaTime = deltaClock.restart().asSeconds();

		

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
		
			} 
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
			{
			
				is_movement = true;
				inhale_direction = false;
		
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getPosition(window)); // Need to specify window
				sf::Vector2f spritePos = sprite.getPosition();

				if ((mousePos.x < spritePos.x && !inhale_direction) || (mousePos.x > spritePos.x && inhale_direction))
				{
					if (fireclock.getElapsedTime().asMilliseconds() > 50)
					{
						fire = true;
						bullets.push_back(bullet);
						bullets[bullets.size() - 1].Ready_Bullet(sprite.getPosition(), Vector2f(Mouse::getPosition(window)));
					}
				}
				
			
			}
			else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::LControl || event.key.code == Keyboard::RControl))
			{
				drink = true;
				
			}
		}

			for (int i = bullets.size()-1; i>= 0; i--)
	      	{ 
			bullets[i].move();  // it will move in the specified direction
			
			// this is for enemy i added random pictures but then i added a a enemy with animation so..
		/*	for (int j = 0; j < enemy_sprites.size(); j++)
			{
				if (bullets[i].get_global_bounds().intersects(enemy_sprites[j].getGlobalBounds()) && enemy_healths[j] > 0)
				{
					enemy_healths[j] -= 10;
					bullets.erase(bullets.begin() + i);
					break;
				}

			}*/



			if (bullets[i].get_global_bounds().intersects(e.Enemy_get_global_bounds()) && e.get_enenmy_health() > 0)
			{
				e.deduct_health();
				bullets.erase(bullets.begin() + i);
				break;
			}
		
		}
     
		if (fire)
		{
			animate.Fire_Animatio(sprite, inhale_direction, fireclock,fire);
		}

		//This is for non stop firing default logic is for single tab fire

		//else if (Mouse::isButtonPressed(Mouse::Left))
		//{
		//	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getPosition(window)); // Need to specify window
		//	sf::Vector2f spritePos = sprite.getPosition();

		//	if ((mousePos.x < spritePos.x && !inhale_direction) || (mousePos.x > spritePos.x && inhale_direction))
		//	{
		//		/*if (fireclock.getElapsedTime().asMilliseconds() > 50)*/
		//		if (1)
		//		{
		//			fire = true;
		//			bullets.push_back(bullet);
		//			bullets[bullets.size() - 1].Ready_Bullet(sprite.getPosition(), Vector2f(Mouse::getPosition(window)));
		//		}
		//	}


		//}

		else if ((Keyboard::isKeyPressed(Keyboard::Right)|| Keyboard::isKeyPressed(Keyboard::Left)) && is_movement)
		{ 
			animate.Forward_Move(sprite, inhale_direction, Movement_clock);
		}
		else if (drink)
		{
			animate.Drink_Animation(sprite, inhale_direction, drink_clock, drink);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)|| Keyboard::isKeyPressed(Keyboard::S))
		{
			animate.Down_Shield(sprite, inhale_direction, Down_shield_clock,down_stay);
		}
		
		else
		{
			animate.Inhale_Animation(sprite, inhale_direction, inhale_clock);
			down_stay = false;
		}
		e.update(deltaTime, sprite.getPosition());
		//sprite.setPosition(animate.Marco_position.x, animate.Marco_position.y+600);

		sprite.setScale(Vector2f(3, 3));
		sf::FloatRect bounds = sprite.getGlobalBounds(); 

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
		if (e.get_enenmy_health()>0)
		{
			e.draw(window);
		}
		

		for (int i = 0; i < bullets.size(); i++)
		{
			
			bullets[i].draw(window);
			
		}
		//for (int i = 0; i < enemy_sprites.size(); i++)
		//{
		//	if (enemy_healths[i] > 0)
		//	{
		//		window.draw(enemy_sprites[i]);
		//	}
		//}
	
		//window.draw(rect);
		window.display();
		
	}
	return 0;
}
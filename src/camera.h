#pragma once
#include <SFML/Graphics.hpp>
#include "marco.h"

using namespace sf;

class Camera
{
	private:
			sf::View view;
			sf::RenderWindow& window;
			float speed;
};
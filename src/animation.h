#pragma once
#include <SFML/Graphics.hpp>
#include "marco.h"

using namespace sf;
class Animation :public Marco
{
private:
	int movement_delay;
	int frame;
	int inhale_delay;
	int inhale_frame;
	int firing_delay;
	int firing_frame;
	int drink_frame;
	int drink_delay;
public:
	Animation();
	void Forward_Move(Sprite& sprite, bool x, Clock& clock);
	void Inhale_Animation(Sprite& sprite, bool x, Clock& clock);
	void Fire_Animatio(Sprite& sprite, bool x, Clock& clock,bool &fire);
	void Drink_Animation(Sprite& sprite, bool x, Clock& clock, bool& fire);

};
#include "animation.h"
//#include"marco.h"

Animation::Animation()
{
	movement_delay = 90;
	frame = 0;
	inhale_delay = 100;
	inhale_frame = 0;
	firing_delay = 50;
	firing_frame = 0;
	drink_delay = 100;
	drink_frame = 0;
	Down_Shield_delay = 150;
	Down_Shield_delay_frame = 0;
	
}

void Animation::Forward_Move(Sprite& sprite,bool x, Clock &clock) // x shows direction of character
{
	if (clock.getElapsedTime().asMilliseconds() >= movement_delay)
	{
		(x)?Marco_position.x += 20.0f: Marco_position.x -= 20.0f;
		if ( frame< 2)
		{
			frame = 2;
		}
		
		sprite = right_movement(frame, x);
		frame = (frame + 1) % 12;
		clock.restart();
	}
	sprite.setPosition(Marco_position.x,Marco_position.y + 600);
}

void Animation::Inhale_Animation(Sprite& sprite, bool x, Clock& clock)
{
	if (clock.getElapsedTime().asMilliseconds()>inhale_delay)
	{
		
	sprite = (x) ? Right_Inhale[inhale_frame]:Left_Inhale[inhale_frame];
	inhale_frame = (inhale_frame + 1) % 8;
	clock.restart();
	}
	sprite.setPosition(Marco_position.x, Marco_position.y + 600);

}

void Animation::Fire_Animatio(Sprite& sprite, bool x, Clock& clock, bool &fire)
{
	int a = -1;
	if (clock.getElapsedTime().asMilliseconds()>firing_delay)
	{
		sprite = (x) ? right_shoot[firing_frame] : left_shoot[firing_frame];
		if (!x)
		{
			sprite.setPosition(Marco_position.x-40, Marco_position.y + 595);
			a = 1;
		}
		firing_frame++;
		if (firing_frame>=4)
		{
			fire = false;
			firing_frame = 0;
		}
		clock.restart();
		if (a == -1)
		{
			sprite.setPosition(Marco_position.x, Marco_position.y + 600);
		}
	}
	
}

void Animation::Drink_Animation(Sprite& sprite, bool x, Clock& clock, bool& drink)
{
	if (clock.getElapsedTime().asMilliseconds()>drink_delay)
	{
		sprite = (x) ? Right_Drink[drink_frame] : Left_Drink[drink_frame];
		drink_frame++;
		if (drink_frame>=14)
		{
			drink_frame = 0;
			drink = false;
		}
		clock.restart();
	sprite.setPosition(Marco_position.x, Marco_position.y + 595);
	}	
}

void Animation::Down_Shield(Sprite& sprite, bool x, Clock& clock,bool &is_complete)
{
	if (!is_complete)
	{
	if (clock.getElapsedTime().asMilliseconds()>=Down_Shield_delay)
	{
		sprite = (x) ? Right_Down[Down_Shield_delay_frame++] : Left_Down[Down_Shield_delay_frame++];
		if (Down_Shield_delay_frame>=4)
		{
			Down_Shield_delay_frame = 0;
			is_complete = true;
		}
		clock.restart();
	}
	//sprite.setPosition(Marco_position.x, Marco_position.y + 595);
	if(Down_Shield_delay_frame<3)
	sprite.setPosition(Marco_position.x, Marco_position.y + 595);
	else
	{
		sprite.setPosition(Marco_position.x, Marco_position.y + 650);
	}
	}
	else
	{
		sprite = (x) ? Right_Down[3] : Left_Down[3];
		sprite.setPosition(Marco_position.x, Marco_position.y + 650);
	}
}

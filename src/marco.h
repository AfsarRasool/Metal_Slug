#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Marco
{
	public:
	Texture texture;
	Sprite right_shoot[4];
	Sprite left_shoot[4];
	Sprite Right_Inhale[8];
	Sprite Left_Inhale[8];
	Sprite Right_Movement[12];
	Sprite Left_Movement[12];
	Sprite Right_Drink[14];
	Sprite Left_Drink[14];
	Sprite Right_Down[4];
	Sprite Left_Down[4];
	//....................

	Vector2f Marco_position;
	Vector2f Marco_Scale;

public:
	Marco();
	void set_down_sprites(Texture &texture, Sprite* right_down_array, Sprite* left_down_array);
	void setposition(Vector2f v);
	Sprite shoot_sprites(int frame_no, bool x);
	Sprite inhale_sprites(int frame_no,bool x);
	Sprite right_movement(int frame_no, bool x);
	Vector2f Get_Marco_position();

};

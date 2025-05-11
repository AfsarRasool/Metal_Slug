#include"marco.h"

Marco::Marco()
{
	texture.loadFromFile("resources/mainC.png");
    //texture.setSmooth(true);
    Marco_Scale = Vector2f(3, 3);
	for (int i = 0; i < 4; i++)
	{
		right_shoot[i].setTexture(texture);
		right_shoot[i].setTextureRect(IntRect(307 + (i * 54), 1486, 54, 40));
		right_shoot[i].setScale(Marco_Scale);
	}
    for (int i = 0; i < 4; i++)
    {
        left_shoot[i].setTexture(texture);
        left_shoot[i].setTextureRect(IntRect(309 - ((i + 1) * 54), 1484, 54, 40));
        
        left_shoot[i].setScale(Marco_Scale);
    }
	// INHALE....................

        // Inhale Right
    for (int i = 0; i < 4; i++) {
        Right_Inhale[i].setTexture(texture);
        //Right_Inhale[i].setTextureRect(IntRect(Sprite_Mid + (i * 40), 20, rect_X, 40)); ////IntRect(309 + (i * 40), 23, 40, 38)
        Right_Inhale[i].setTextureRect(IntRect(309 + (i * 40), 23, 40, 38));
        //Right_Inhale[i].setPosition(100, 700);
        Right_Inhale[i].setScale(Marco_Scale);
    }
    for (int i = 0; i < 4; i++) {
        Right_Inhale[4 + i] = Right_Inhale[4 - i - 1];
    }
    // Inhale Left
    for (int i = 0; i < 4; i++) {
        Left_Inhale[i].setTexture(texture);
        Left_Inhale[i].setTextureRect(IntRect(307 - ((i + 1) * 40), 23, 40, 38));
        //Left_Inhale[i].setPosition(100, 700);
        Left_Inhale[i].setScale(Marco_Scale);
    }
    for (int i = 0; i < 4; i++) {
        Left_Inhale[4 + i] = Left_Inhale[4 - i - 1];
    }
    //Right Ahead-Movement
    for (int i = 0; i < 6; i++)
    {
        Right_Movement[i].setTexture(texture);
        Right_Movement[i].setTextureRect(IntRect(308 + (i * 38), 1113, 38, 40));  //309,1115
        //Right_Movement[i].setPosition(100, 775);
        Right_Movement[i].setScale(Marco_Scale);
    }
    for (int i = 0; i < 6; i++)
    {
        Right_Movement[i + 6].setTexture(texture);
        Right_Movement[i + 6].setTextureRect(IntRect(308 + (i * 40), 1162, 40, 40));
        Right_Movement[i + 6].setScale(Marco_Scale);
        //Right_Movement[i + 6].setPosition(100, 775);
    }
    //Left Movement
    for (int i = 0; i < 6; i++)
    {
        Left_Movement[i].setTexture(texture);
        Left_Movement[i].setTextureRect(IntRect(308 - ((i + 1) * 38), 1113, 38, 40));
        // Left_Movement[i].setPosition(100, 700);
        Left_Movement[i].setScale(Marco_Scale);
    }
    for (int i = 0; i < 6; i++)
    {
        Left_Movement[i + 6].setTexture(texture);
        Left_Movement[6 + i].setTextureRect(IntRect(306 - ((i + 1) * 40), 1160, 40, 40));
        Left_Movement[6 + i].setScale(Marco_Scale);
    }
    // Drink
    for (int i = 0; i < 7; i++) {  /// right Drink
        Right_Drink[i].setTexture(texture);
        Right_Drink[i].setTextureRect(IntRect(308 + (i * 40), 70, 40, 40));//IntRect(307 + (i * 41), 65, rect_X, 48)
        Right_Drink[i].setScale(Marco_Scale);
    }
    for (int i = 0; i < 7; i++) {
        Right_Drink[i + 7] = Right_Drink[7 - i - 1];
    }
    for (int i = 0; i < 7; i++) {  // Left Drink
        Left_Drink[i].setTexture(texture);
        Left_Drink[i].setTextureRect(IntRect(308 - ((i + 1) * 40), 70, 40, 40));
        Left_Drink[i].setScale(Marco_Scale);
    }
    for (int i = 0; i < 7; i++) {
        Left_Drink[i + 7] = Left_Drink[7 - i - 1];
    }
    //for (int i = 0; i < 7; i++) {  // Left D
    //     Right_Down[i].setTexture(texture);
    //     Right_Down[i].setTextureRect(IntRect(308 - ((i + 1) * 40), 912, 40, 43));
    //     Right_Down[i].setScale(Marco_Scale);
    //}

    // Right Down Shield
    set_down_sprites(texture, Right_Down, Left_Down);  // this is because in this animation i have to apply different rect size for sprite

}

void Marco::set_down_sprites(Texture &texture, Sprite* right_down_array, Sprite* left_down_array)
{
   //Right
    for (int i = 0; i <2 ; i++)
    {
        right_down_array[i].setTexture(texture);
        right_down_array[i].setTextureRect(IntRect(308+(i*40), 915, 40, 40));
    }
    right_down_array[2].setTexture(texture);
    right_down_array[2].setTextureRect(IntRect(308 + (2 * 40), 930, 34, 24));
    right_down_array[3].setTexture(texture);
    right_down_array[3].setTextureRect(IntRect(429 , 930, 34, 24));
  //  Left
    for (int i = 0; i < 2; i++)
    {
        left_down_array[i].setTexture(texture);
        left_down_array[i].setTextureRect(IntRect(309 - ((i+1) * 40), 915, 40, 40));
    }
    left_down_array[2].setTexture(texture);
    left_down_array[2].setTextureRect(IntRect(309 - (3 * 40), 930, 34, 24));
    left_down_array[3].setTexture(texture);
    left_down_array[3].setTextureRect(IntRect(153, 930, 34, 24));
}


void Marco::setposition(Vector2f v)
{
	Marco_position = v;
}

Sprite Marco::shoot_sprites(int frame_no,bool x)
{
	return right_shoot[frame_no];
}

Sprite Marco::inhale_sprites(int frame_no, bool x) //
{

	if (x)
			return Right_Inhale[frame_no];
	else
		   return Left_Inhale[frame_no];
}

Sprite Marco::right_movement(int frame_no, bool x)
{
    if (x)
        return Right_Movement[frame_no];
    else
        return Left_Movement[frame_no];
}

Vector2f Marco::Get_Marco_position()
{
	return Marco_position;
}



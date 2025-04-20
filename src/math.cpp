#include <SFML/Graphics.hpp>
#include"Math.h"
using namespace sf;


 Vector2f Math::Nomalize_vector(Vector2f v)
{
    
        float magnitude = sqrt(pow(v.x, 2) + pow(v.y + 100, 2));
        Vector2f normalized_vec;
        normalized_vec.x = v.x / magnitude;
        normalized_vec.y = v.y / magnitude;

       return normalized_vec;
    
    
}

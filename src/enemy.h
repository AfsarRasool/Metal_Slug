#pragma once

#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Enemy 
{
private:
   
        sf::Texture texture;
        sf::Sprite sprite;

        int currentFrame = 0;
        float scaleFactor = 2.76f;
        bool facingLeft = true;
        bool isMoving = false;

        float walkFrameDuration = 0.1f;
        float idleFrameDuration = 0.28f;
        sf::Clock animationClock;

        sf::Clock aiClock;
        float aiIdleDuration = 2.0f;
        float aiMoveDuration = 2.7f;
        float movementCooldown = 0.f;
        bool moveRight = true;
        float patrolSpeed = 50.0f;

        float walkFrameWidths[11] = { 41, 39, 39, 40, 42, 41, 41, 41, 41, 41, 42 };
        float idleFrameWidths[6] = { 41, 41, 40, 38, 38, 38 };
        int numWalkFrames = 11;
        int numIdleFrames = 6;
        int firstWalkFrameX = 17;
        int firstIdleFrameX = 243;
        int walkYPos = 52;
        int idleYPos = 2;

        bool isAware = false;
        int enenmy_health = 100;

public:
    Enemy();
    void updateFacing(sf::Vector2f playerPos);
    void updateAnimation();
    void updateAI(float deltaTime, sf::Vector2f playerPos);
    void update(float deltaTime, sf::Vector2f playerPos);
    void update(float);
    void draw(sf::RenderWindow& window);
    FloatRect Enemy_get_global_bounds();

    void deduct_health();

    int get_enenmy_health();

};
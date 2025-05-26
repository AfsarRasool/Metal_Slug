#include"enemy.h"


float getDistance(sf::Vector2f a, sf::Vector2f b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

Enemy::Enemy() {
    if (!texture.loadFromFile("resources/character_sprite_sheet.png")) {
        exit(-1);
    }
    sprite.setTexture(texture);
    sprite.setScale(scaleFactor, scaleFactor);
    sprite.setPosition(950, 600);
    sprite.setTextureRect(sf::IntRect(firstIdleFrameX, idleYPos, idleFrameWidths[0], 48));
}

void Enemy::updateFacing(sf::Vector2f playerPos) {
    sf::Vector2f enemyPos = sprite.getPosition();
    if (playerPos.x < enemyPos.x && !facingLeft) {
        facingLeft = true;
        sprite.setScale(-scaleFactor, scaleFactor);
        sprite.setOrigin(walkFrameWidths[currentFrame], 0.f);
    }
    else if (playerPos.x > enemyPos.x && facingLeft) {
        facingLeft = false;
        sprite.setScale(scaleFactor, scaleFactor);
        sprite.setOrigin(0.f, 0.f);
    }
}


void Enemy:: updateAnimation() {
    if (isMoving && animationClock.getElapsedTime().asSeconds() > walkFrameDuration) {
        currentFrame = (currentFrame + 1) % numWalkFrames;
        int x = firstWalkFrameX;
        for (int i = 0; i < currentFrame; i++) x += walkFrameWidths[i] + 2;
        sprite.setTextureRect(sf::IntRect(x, walkYPos, walkFrameWidths[currentFrame], 43));
        animationClock.restart();
    }
    else if (!isMoving && animationClock.getElapsedTime().asSeconds() > idleFrameDuration) {
        currentFrame = (currentFrame + 1) % numIdleFrames;
        int x = firstIdleFrameX;
        for (int i = 0; i < currentFrame; i++) x += idleFrameWidths[i] + 1;
        sprite.setTextureRect(sf::IntRect(x, idleYPos, idleFrameWidths[currentFrame], 48));
        animationClock.restart();
    }                           
}

void  Enemy::updateAI(float deltaTime, sf::Vector2f playerPos) {
    sf::Vector2f enemyPos = sprite.getPosition();
    float distance = getDistance(enemyPos, playerPos);
    float detectionRange = 500.f;  // Radius at which the enemy becomes aware of the player

    isMoving = false;
    sf::Vector2f moveDelta(0.f, 0.f);


    if (distance <= detectionRange)
    {
        if (!isAware) {
            isAware = true;
        }

        updateFacing(playerPos);  // Only face the player
        // No movement logic
    }
    else if (!isAware) {
        // If the enemy is not aware, it can patrol (optional, you can remove this logic if no patrol behavior is desired)
        movementCooldown += deltaTime;
        if (movementCooldown >= aiIdleDuration) {
            updateFacing({ enemyPos.x + (moveRight ? 1.f : -1.f), enemyPos.y });  // Ensure the enemy faces the correct direction
            moveDelta.x = (moveRight ? patrolSpeed : -patrolSpeed) * deltaTime;
            isMoving = true;

            if (movementCooldown >= aiIdleDuration + aiMoveDuration) {
                moveRight = !moveRight;
                movementCooldown = 0.f;
            }
        }
    }

    sprite.move(moveDelta);
}



void Enemy::update(float deltaTime, sf::Vector2f playerPos) {
    updateAI(deltaTime, playerPos);
    updateAnimation();
}

void Enemy::update(float)  {} // Not used, overload for OOP interface

void Enemy::draw(sf::RenderWindow& window)  {
    window.draw(sprite);
}

FloatRect Enemy::Enemy_get_global_bounds()
{
    return sprite.getGlobalBounds();
}

void Enemy::deduct_health()
{
   
        enenmy_health -= 20;
    
}

int Enemy::get_enenmy_health()
{
    return enenmy_health;
}

// collision.cpp
#include "collision.h"


bool checkCollision (const SDL_Rect& a, const SDL_Rect& b)
{
    return SDL_HasIntersection(&a, &b);
}

bool checkHelicopterCollision (Helicopter& helicopter, std::vector<Obstacle>& obstacles)
{
    SDL_Rect helicopterRect = helicopter.getCollider();
    
    for (const auto& obstacle : obstacles)
    {
        if (checkCollision(helicopterRect, obstacle.getCollider()))
        {
            return true;
        }
    }
    
    return false;
}

bool checkScreenCollision (Helicopter& helicopter)
{
    SDL_Rect helicopterRect = helicopter.getCollider();
    
    if (helicopterRect.x < 0 || helicopterRect.x + helicopterRect.w > SCREEN_WIDTH || helicopterRect.y < 0 || helicopterRect.y + helicopterRect.h > SCREEN_HEIGHT)
    {
        return true;
    }
    
    return false;
}

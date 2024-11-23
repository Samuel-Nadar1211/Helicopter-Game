// obstacle.cpp
#include "obstacle.h"


Obstacle::Obstacle (SDL_Renderer* renderer, SDL_Texture* texture)
    : renderer(renderer), texture(texture)
{
    posX = static_cast<float> (SCREEN_WIDTH);
    posY = static_cast<float> (rand() % (SCREEN_HEIGHT - 200));
    velocityX = -200.0f;

    rect = { static_cast<int> (posX), static_cast<int> (posY), 100, 200 };
}

void Obstacle::update(float deltaTime)
{
    posX += velocityX * deltaTime;
    rect.x = static_cast<int>(posX);
}

void Obstacle::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Obstacle::isOffScreen() const
{
    return posX + rect.w < 0;
}

SDL_Rect Obstacle::getCollider() const
{
    return rect;
}

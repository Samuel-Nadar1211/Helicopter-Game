// obstacle.h
#pragma once

#include "loader.h"

#include <cstdlib>


class Obstacle
{
public:
    Obstacle (SDL_Renderer* renderer, SDL_Texture* texture);

    void update (float deltaTime);
    void render (SDL_Renderer* renderer);

    bool isOffScreen() const;
    SDL_Rect getCollider() const;

private:
    float posX, posY;
    float velocityX;
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
};
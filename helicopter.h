// helicopter.h

#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "loader.h"


const float HELICOPTER_INITIAL_VELOCITY_Y = -200.0f;
const float GRAVITY = 50 * 9.80f;
const int HELICOPTER_WIDTH = 150;
const int HELICOPTER_HEIGHT = 50;


class Helicopter
{
public:
    Helicopter (SDL_Renderer* renderer, const std::string& texturePath);
    ~Helicopter();

    void handleInput (SDL_Event* e);
    void update (float deltaTime);
    void render (SDL_Renderer* renderer);

    SDL_Rect getCollider() const;
    void crash(SDL_Texture* crashTexture);
    bool isCrashed() const;
    void respawn (SDL_Renderer* renderer, const std::string& texturePath);

private:
    float posX, posY;
    float velY;
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    bool crashed;

    SDL_Texture* loadTexture (const std::string& path);
};


#endif  // !HELICOPTER_H

// helicopter.cpp
#include "helicopter.h"


Helicopter::Helicopter (SDL_Renderer* renderer, const std::string& texturePath)
    : posX(SCREEN_WIDTH / 8.0f), posY(SCREEN_HEIGHT / 2.0f), velY(0.0f), renderer(renderer), crashed(false)
{
    texture = loadTexture (texturePath);
    if (texture == nullptr)
    {
        std::cerr << "Failed to load texture image!" << std::endl;
    }

    rect = { static_cast<int> (posX), static_cast<int> (posY), HELICOPTER_WIDTH, HELICOPTER_HEIGHT };
}

Helicopter::~Helicopter()
{
    SDL_DestroyTexture(texture);
}

void Helicopter::handleInput (SDL_Event* e)
{
    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE)
    {
        velY = HELICOPTER_INITIAL_VELOCITY_Y;
    }
}

void Helicopter::update (float deltaTime)
{
    velY += GRAVITY * deltaTime;
    posY += velY * deltaTime;
    rect.y = static_cast<int> (posY);
}

void Helicopter::render (SDL_Renderer* renderer)
{
    SDL_RenderCopy (renderer, texture, nullptr, &rect);
}

SDL_Texture* Helicopter::loadTexture (const std::string& path)
{
    return ::loadTexture(path, renderer);
}

SDL_Rect Helicopter::getCollider() const
{
    return rect;
}

void Helicopter::crash (SDL_Texture* crashTexture)
{
    crashed = true;
    SDL_DestroyTexture(texture);
    texture = crashTexture;
}

bool Helicopter::isCrashed() const
{
    return crashed;
}

void Helicopter::respawn (SDL_Renderer* renderer, const std::string& texturePath)
{
    posX = SCREEN_WIDTH / 8.0f;
    posY = SCREEN_HEIGHT / 2.0f;
    velY = 0.0f;
    this->renderer = renderer;
    crashed = false;
    
    texture = loadTexture (texturePath);

    if (texture == nullptr)
    {
        std::cerr << "Failed to load texture image!" << std::endl;
    }

    rect = { static_cast<int> (posX), static_cast<int> (posY), HELICOPTER_WIDTH, HELICOPTER_HEIGHT };
}
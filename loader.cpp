// loader.cpp
#include "loader.h"


bool init (SDL_Window** window, SDL_Renderer** renderer)
{
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow ("Helicopter Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer (*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);


    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init (imgFlags) & imgFlags))
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Texture* loadTexture (const std::string& path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr)
    {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface (renderer, loadedSurface);
        SDL_FreeSurface (loadedSurface);
    }
    return newTexture;
}

void close (SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Texture* obstacleTexture, SDL_Texture* crashHelicopterTexture, SDL_Texture* gameOverTexture, SDL_Texture* topScoreTexture, TTF_Font* font, Mix_Chunk* helicopterSound, Mix_Chunk* crashSound, Mix_Music* winnerMusic)
{
    if (backgroundTexture != nullptr)
    {
        SDL_DestroyTexture (backgroundTexture);
        backgroundTexture = nullptr;
    }

    if (obstacleTexture != nullptr)
    {
        SDL_DestroyTexture (obstacleTexture);
        obstacleTexture = nullptr;
    }

    if (crashHelicopterTexture != nullptr)
    {
        SDL_DestroyTexture (crashHelicopterTexture);
        crashHelicopterTexture = nullptr;
    }

    if (gameOverTexture != nullptr)
    {
        SDL_DestroyTexture (gameOverTexture);
        gameOverTexture = nullptr;
    }

    if (topScoreTexture != nullptr)
    {
        SDL_DestroyTexture (topScoreTexture);
        topScoreTexture = nullptr;
    }

    if (renderer != nullptr)
    {
        SDL_DestroyRenderer (renderer);
        renderer = nullptr;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow (window);
        window = nullptr;
    }


    if (font != nullptr)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (helicopterSound != nullptr)
    {
        Mix_FreeChunk (helicopterSound);
        helicopterSound = nullptr;
    }

    if (crashSound != nullptr)
    {
        Mix_FreeChunk (crashSound);
        crashSound = nullptr;
    }

    if (winnerMusic != nullptr)
    {
        Mix_FreeMusic (winnerMusic);
        winnerMusic = nullptr;
    }


    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    TTF_Quit();
}
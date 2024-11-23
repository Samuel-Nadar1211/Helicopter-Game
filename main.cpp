// main.cpp
#include "collision.h"
#include "score.h"

#include <vector>
#include <ctime>


void render (SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Texture* gameOverTexture, SDL_Texture* topScoreTexture, Helicopter& helicopter, std::vector<Obstacle>& obstacles, TTF_Font* font, int highScore, int score)
{
    SDL_RenderCopy (renderer, backgroundTexture, nullptr, nullptr);
    helicopter.render (renderer);

    for (auto& obstacle : obstacles)
    {
        obstacle.render (renderer);
    }

    renderScore(renderer, font, highScore, score);


    if (helicopter.isCrashed())
    {
        if (highScore < score)
        {
            SDL_Rect topScoreRect;
            topScoreRect.x = (SCREEN_WIDTH - 400) / 2;
            topScoreRect.y = (SCREEN_HEIGHT - 400) / 2;
            topScoreRect.w = 400;
            topScoreRect.h = 400;
            SDL_RenderCopy(renderer, topScoreTexture, nullptr, &topScoreRect);
        }
        else
        {
            SDL_Rect gameOverRect;
            gameOverRect.x = (SCREEN_WIDTH - 500) / 2;
            gameOverRect.y = (SCREEN_HEIGHT - 300) / 2;
            gameOverRect.w = 500;
            gameOverRect.h = 300;
            SDL_RenderCopy(renderer, gameOverTexture, nullptr, &gameOverRect);
        }
    }
}


int main (int argc, char* args[])
{
    srand (static_cast<unsigned int> (time(0)));

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init (&window, &renderer))
    {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    SDL_Texture* backgroundTexture = loadTexture ("Images/background.png", renderer);
    if (backgroundTexture == nullptr)
    {
        std::cerr << "Failed to load background texture!" << std::endl;
        close (window, renderer);
        return -1;
    }

    SDL_Texture* obstacleTexture = loadTexture ("Images/obstacle.png", renderer);
    if (obstacleTexture == nullptr)
    {
        std::cerr << "Failed to load obstacle texture!" << std::endl;
        close(window, renderer, backgroundTexture);
        return -1;
    }

    SDL_Texture* crashHelicopterTexture = loadTexture ("Images/crash helicopter.png", renderer);
    if (crashHelicopterTexture == nullptr)
    {
        std::cerr << "Failed to load crash helicopter texture!" << std::endl;
        close(window, renderer, backgroundTexture, obstacleTexture);
        return -1;
    }

    SDL_Texture* gameOverTexture = loadTexture ("Images/game over.png", renderer);
    if (gameOverTexture == nullptr)
    {
        std::cerr << "Failed to load game over texture!" << std::endl;
        close(window, renderer, backgroundTexture, obstacleTexture, crashHelicopterTexture);
        return -1;
    }
    
    SDL_Texture* topScoreTexture = loadTexture ("Images/top score.png", renderer);
    if (topScoreTexture == nullptr)
    {
        std::cerr << "Failed to load top score texture!" << std::endl;
        close(window, renderer, backgroundTexture, obstacleTexture, crashHelicopterTexture, gameOverTexture);
        return -1;
    }

    TTF_Font* font = loadFont ("Fonts/girassol.ttf", 36);
    if (font == nullptr)
    {
        close(window, renderer, backgroundTexture, obstacleTexture, crashHelicopterTexture, gameOverTexture, topScoreTexture);
        return -1;
    }


    Mix_Chunk* helicopterSound = Mix_LoadWAV ("Audios/helicopter.wav");
    if (helicopterSound == nullptr)
    {
        std::cerr << "Failed to load helicopter sound: " << Mix_GetError() << std::endl;
        close(window, renderer, backgroundTexture, obstacleTexture, crashHelicopterTexture, gameOverTexture, topScoreTexture, font);
        return -1;
    }

    Mix_Chunk* crashSound = Mix_LoadWAV ("Audios/crash.wav");
    if (crashSound == nullptr)
    {
        std::cerr << "Failed to load crash sound: " << Mix_GetError() << std::endl;
        close(window, renderer, backgroundTexture, obstacleTexture, crashHelicopterTexture, gameOverTexture, topScoreTexture, font, helicopterSound);
        return -1;
    }

    Mix_Music* winnerMusic = Mix_LoadMUS ("Audios/winner.mp3");
    if (winnerMusic == nullptr)
    {
        std::cerr << "Failed to load winner music: " << Mix_GetError() << std::endl;
        close(window, renderer, backgroundTexture, obstacleTexture, crashHelicopterTexture, gameOverTexture, topScoreTexture, font, helicopterSound, crashSound);
        return -1;
    }


    Helicopter helicopter (renderer, "Images/helicopter.png");
    std::vector<Obstacle> obstacles;

    int highScore = readHighScore();
    int score = -2;

    bool quit = false;
    bool gameOver = false;
    SDL_Event e;
    Uint32 startTicks = SDL_GetTicks();
    Uint32 lastObstacleSpawnTime = 0;
    const Uint32 obstacleInterval = 2000;   // 2 seconds interval

    Mix_PlayChannel (-1, helicopterSound, -1);

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (gameOver)
            {
                if (e.type == SDL_KEYDOWN)
                {
                    if (highScore < score)
                    {
                        highScore = score;
                    }

                    score = -2;
                    gameOver = false;
                    
                    obstacles.clear();
                    helicopter.respawn (renderer, "Images/helicopter.png");
                    startTicks = SDL_GetTicks();
                    Mix_PlayChannel(-1, helicopterSound, -1);
                }
            }
            else
            {
                helicopter.handleInput(&e);
            }
        }

        if (!gameOver)
        {
            Uint32 currentTicks = SDL_GetTicks();
            float deltaTime = (currentTicks - startTicks) / 1000.0f;
            startTicks = currentTicks;

            helicopter.update (deltaTime);

            if (currentTicks - lastObstacleSpawnTime > obstacleInterval)
            {
                score++;
                obstacles.emplace_back (renderer, obstacleTexture);
                lastObstacleSpawnTime = currentTicks;
            }

            for (auto it = obstacles.begin(); it != obstacles.end(); )
            {
                it->update (deltaTime);
            
                if (it->isOffScreen())
                {
                    it = obstacles.erase(it);
                }
                else
                {
                    it++;
                }
            }

            if (checkHelicopterCollision (helicopter, obstacles) || checkScreenCollision (helicopter))
            {
                Mix_HaltChannel(-1);
                Mix_PlayChannel(-1, crashSound, 0);
                helicopter.crash (crashHelicopterTexture);
                gameOver = true;

                if (score > highScore)
                {
                    Mix_PlayMusic (winnerMusic, 1);
                    writeHighScore (score);
                }
            }

            SDL_SetRenderDrawColor (renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear (renderer);

            render (renderer, backgroundTexture, gameOverTexture, topScoreTexture, helicopter , obstacles, font, highScore, score);

            SDL_RenderPresent (renderer);
        }
    }

    close (window, renderer, backgroundTexture, obstacleTexture, crashHelicopterTexture, gameOverTexture, topScoreTexture, font, helicopterSound, crashSound, winnerMusic);

    return 0;
}

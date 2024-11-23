// score.cpp

#include "score.h"
#include <fstream>


TTF_Font* loadFont(const std::string& path, int fontSize)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
    if (font == nullptr)
    {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    return font;
}

SDL_Texture* renderText(const std::string& message, SDL_Renderer* renderer, TTF_Font* font)
{
    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Surface* surf = TTF_RenderText_Solid (font, message.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface (renderer, surf);
    SDL_FreeSurface(surf);
    return texture;
}

void renderScore(SDL_Renderer* renderer, TTF_Font* font, int highScore, int score)
{
    SDL_Texture* scoreTexture = renderText("Your Score: " + std::to_string(score < 0 ? 0 : score), renderer, font);
    SDL_Rect scoreRect = { 10, 10, 250, 35 };
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
    SDL_DestroyTexture(scoreTexture);

    SDL_Texture* highScoreTexture = renderText("High Score: " + std::to_string(highScore), renderer, font);
    SDL_Rect highScoreRect = { SCREEN_WIDTH - 260, 10, 250, 35 };
    SDL_RenderCopy(renderer, highScoreTexture, nullptr, &highScoreRect);
    SDL_DestroyTexture(highScoreTexture);
}

int readHighScore()
{
    std::ifstream file ("highscore.dat", std::ios::binary);
    int highScore = 0;
    if (file.is_open())
    {
        file.read (reinterpret_cast<char*>(&highScore), sizeof(highScore));
        file.close();
    }
    return highScore;
}

void writeHighScore(int highScore)
{
    std::ofstream file ("highscore.dat", std::ios::binary);
    if (file.is_open())
    {
        file.write (reinterpret_cast<const char*>(&highScore), sizeof(highScore));
        file.close();
    }
}
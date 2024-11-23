// loader.h
#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


bool init (SDL_Window** window, SDL_Renderer** renderer);

SDL_Texture* loadTexture (const std::string& path, SDL_Renderer* renderer);

void close(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* backgroundTexture = nullptr, SDL_Texture* obstacleTexture = nullptr, SDL_Texture* crashHelicopterTexture = nullptr, SDL_Texture* gameOverTexture = nullptr, SDL_Texture* topScoreTexture = nullptr, TTF_Font* font = nullptr, Mix_Chunk* helicopterSound = nullptr, Mix_Chunk* crashSound = nullptr, Mix_Music* winnerMusic = nullptr);

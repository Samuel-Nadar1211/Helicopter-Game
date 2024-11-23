// score.h
#pragma once

#include "loader.h"


TTF_Font* loadFont(const std::string& path, int fontSize);

void renderScore(SDL_Renderer* renderer, TTF_Font* font, int highScore, int score);

int readHighScore();

void writeHighScore(int highScore);

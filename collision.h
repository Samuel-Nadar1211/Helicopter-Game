// collision.h
#pragma once

#include <SDL.h>
#include "helicopter.h"
#include "obstacle.h"
#include <vector>


bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

bool checkHelicopterCollision(Helicopter& helicopter, std::vector<Obstacle>& obstacles);

bool checkScreenCollision(Helicopter& helicopter);

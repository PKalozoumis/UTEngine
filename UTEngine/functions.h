#pragma once

#include "json.hpp"
#include "SDL.h"
#include <iostream>
#include "color.h"

nlohmann::json jsonLoad(std::string filename);

bool withinRange(const double,const double, const double);

SDL_Rect* createRectangle(int x, int y, int width, int height);

void drawRectangle(int x1, int y1, int x2, int y2, int thickness);

void drawRectangleColor(int x1, int y1, int x2, int y2, int thickness, SDL_Color color);

inline void drawResetColor(void);

void drawSetColor(SDL_Color color);

void drawMenuBox(int x1, int y1, int x2, int y2);

bool buttonPressed();

bool button();

bool buttonReleased();

bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);

void stringReplace(std::string& string, char a, char b);

std::string jsonToString(nlohmann::json json);

template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

void cycle(int& value, int min, int max, bool minInclude, bool maxInclude, bool loop, std::string axis, int amount = 1);


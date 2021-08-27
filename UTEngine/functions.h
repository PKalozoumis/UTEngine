#pragma once

#include "json.hpp"
#include "SDL.h"
#include <iostream>
#include "color.h"
#include "Text.h"

nlohmann::json jsonLoad(std::string filename);

bool withinRange(const double num,const double lower, const double upper);

SDL_Rect* createRectangle(int x, int y, int width, int height);

void drawRectangle(int x1, int y1, int x2, int y2, int thickness);

void drawRectangleColor(int x1, int y1, int x2, int y2, int thickness, SDL_Color color);

void drawRectangleColorFilled(int x1, int y1, int x2, int y2, int thickness, SDL_Color outlineColor, SDL_Color fillColor);

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

void drawText(int x, int y, std::string text, std::string font = "fnt_main", SDL_Color textColor = c_white, OutlineType outlineType = full, SDL_Color outlineColor = c_null, float xscale = 1, float yscale = 1);


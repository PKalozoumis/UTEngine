#include "functions.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "SDL.h"
#include "Game.h"
#include "color.h"
#include <cmath>
#include "Controller.h"
#include "Text.h"

nlohmann::json jsonLoad(std::string filename)
{
    std::ifstream myFile(filename);
    nlohmann::json j;

    if(!myFile)
    {
        std::cout<<"The file could not be opened!"<<std::endl;
        exit(-1);
    }

    myFile >> j;
    myFile.close();

    return j;
}

bool withinRange(const double num,const double lower,const double upper)
{
    if((num >= lower) && (num <= upper))
    {
        return true;
    }
    else return false;
}

SDL_Rect* createRectangle(int x, int y, int w, int h)
{
    SDL_Rect* rect = new SDL_Rect();
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    return rect;
}

void drawRectangle(int x1, int y1, int x2, int y2, int thickness)
{
    drawSetColor(c_white);

    if(thickness > 0)
    {
        for(int i = 0; i < thickness; i++)
        {
            SDL_RenderDrawRect(Game::renderer, createRectangle(x1 + i, y1 + i, x2-x1 - 2*i, y2-y1 - 2*i));
        }
    }
   // else SDL_RenderFillRect(Game::renderer, createRectangle(x1, y1, x2-x1, y2-y1));

    drawResetColor();
}

void drawMenuBox(int x1, int y1, int x2, int y2)
{
    drawRectangleColorFilled(x1,y1,x2,y2,3,c_white,c_black);
}

void drawRectangleColor(int x1, int y1, int x2, int y2, int thickness, SDL_Color c)
{
    drawSetColor(c);

    if(thickness > 0)
    {
        for(int i = 0; i < thickness; i++)
        {
            SDL_RenderDrawRect(Game::renderer, createRectangle(x1 + i, y1 + i, x2-x1 - 2*i, y2-y1 - 2*i));
        }
    }
    //else SDL_RenderFillRect(Game::renderer, createRectangle(x1, y1, x2-x1, y2-y1));

    drawResetColor();
}

void drawRectangleColorFilled(int x1, int y1, int x2, int y2, int thickness, SDL_Color outlineColor, SDL_Color fillColor)
{
    drawSetColor(fillColor);

    SDL_RenderFillRect(Game::renderer, createRectangle(x1, y1, x2-x1, y2-y1));

    drawSetColor(outlineColor);

    if(thickness > 0)
    {
        for(int i = 0; i < thickness; i++)
        {
            SDL_RenderDrawRect(Game::renderer, createRectangle(x1 + i, y1 + i, x2-x1 - 2*i, y2-y1 - 2*i));
        }
    }

    drawResetColor();
}

inline void drawResetColor()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void drawSetColor(SDL_Color color)
{
    SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
}

bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    if (
        (rectA.x + rectA.w >= rectB.x)&&
        (rectB.x + rectB.w >= rectA.x)&&
        (rectA.y + rectA.h >= rectB.y)&&
        (rectB.y + rectB.h >= rectA.y)
       )
    {
        return true;
    }

    return false;
}

void stringReplace(std::string& string, char a, char b)
{
    for (int i = 0; i < string.length(); i++)
    {
        if (string[i] == a)
        {
            string[i] = b;
        }
    }
}

std::string jsonToString(nlohmann::json json)
{
    std::string ret = json.dump();

    ret.erase(ret.begin());
    ret.erase(ret.end() - 1);

    return ret;
}

void cycle(int& value, int min, int max, bool minInclude, bool maxInclude, bool loop, std::string axis, int amount)
{
    std::string posButton, negButton;

    if (axis == "horizontal")
    {
        posButton = "keyRight";
        negButton = "keyLeft";
    }
    else if (axis == "vertical")
    {
        posButton = "keyDown";
        negButton = "keyUp";
    }

    if (Controller::buttonPressed(posButton))
    {
        if (value + amount <= max - maxInclude?0:1)
            value += amount;
        else if (loop)
            value = min;
    }
    else if (Controller::buttonPressed(negButton))
    {
        if (value - amount >= min + minInclude?0:1)
            value -= amount;
        else if (loop)
            value = max;
    }
}

void drawText(int x, int y, std::string text, std::string font, SDL_Color textColor, OutlineType outlineType, SDL_Color outlineColor, float xscale, float yscale)
{
    Text* txt = new Text(x,y,text,font,textColor,outlineType,outlineColor,xscale,yscale,true);

    txt->update();
    txt->draw();

    delete txt;
}
#pragma once
#include <iostream>
#include "SDL_ttf.h"
#include "SDL.h"
#include "color.h"
#include <vector>

extern int deltaTime;

enum OutlineType
{
	left_center,
	left_top,
	center_top,
	right_top,
	right_center,
	right_bottom,
	center_bottom,
	left_bottom,
	none,
	full,
	discount
};

class Text
{
	private:
		std::string text;
		int textLength;
		TTF_Font* font = nullptr;
		SDL_Texture* texture = nullptr;
		SDL_Texture* outlineTexture = nullptr;
		SDL_Texture** textureArray;
		SDL_Rect* positionArray;
		TTF_Font** fontArray;
		std::vector<int> splitPos;
		OutlineType outlineType;

		int maxChara = 34;
		int spacing = 8;
		float xscale, yscale;
		int trueWidth, trueHeight;

		bool simpleText;
		
		SDL_Rect pos, outlinePos, textboxPos;
		SDL_Color textColor, outlineColor;

	public:
		Text(int x, int y, std::string text, std::string font = "fnt_main", SDL_Color textColor = c_white, OutlineType outlineType = full, SDL_Color outlineColor = c_null, float xscale = 1, float yscale = 1, bool simpleText = false);
		~Text(void);
		void refreshText(std::string text);
		void refreshOutline(void);
		void setColor(SDL_Color color);
		void setOutlineColor(SDL_Color color);
		void setScale(float xscale, float yscale);
		void draw(void);
		void update(void);
};


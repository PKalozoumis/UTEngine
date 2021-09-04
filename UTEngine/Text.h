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
		int trueWidth, trueHeight;
		bool simpleText;

		std::vector<char> letters;
		std::vector<TTF_Font*> fonts;
		std::vector<OutlineType> outlines;
		std::vector<SDL_Color> colors, outlineColors;
		std::vector<std::pair<int, int>> scale;
		std::vector<SDL_Rect> positions;
		std::vector<int> splitPos;
		
		int alarm = -1;
		int line = 0;
		int currentLetterIndex = 0;

		int maxChara = 33; //34 is the absolute MAX if you wanna be practical, it just looks ugly as hell
		int spacing = 8;
		int xgap = 14;
		int ygap = 10;

		bool createdOutline = false;
		SDL_Color previousColor, previousOutlineColor;
		OutlineType previousType;
		std::string previousText;

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
		int getWidth(void);
		int getHeight(void);
		SDL_Rect getPos(void);
};


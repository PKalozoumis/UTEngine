#include "Text.h"
#include "SDL_ttf.h"
#include "Game.h"
#include "color.h"
#include "functions.h"
#include "Controller.h"
#include <vector>

Text::Text(int x, int y, std::string text, std::string font, SDL_Color textColor, OutlineType outlineType, SDL_Color outlineColor, float xscale, float yscale, bool simpleText)
{
	textLength = text.length();
	this->xscale = xscale;
	this->yscale = yscale;
	this->outlineType = outlineType;
	pos.x = x;
	pos.y = y;
	this->font = Game::fontRegistry[font];
	this->textColor = textColor;
	this->outlineColor = outlineColor;
	this->simpleText = simpleText;
	this->text = text;

	textureArray = new SDL_Texture*[text.length()];
	positionArray = new SDL_Rect[text.length()];
	fontArray = new TTF_Font*[text.length()];

	if (!simpleText)
	{
		SDL_Rect tempPos = {0,0,0,0};

		textboxPos.x = 16;
		textboxPos.y = 160;

		pos.x = textboxPos.x + xgap;
		pos.y = textboxPos.y + ygap;

		#pragma region ======================================= SPLITTING =======================================

		std::string tempText = text;

		splitPos.push_back(0);

		while (splitPos[line] < textLength)
		{
			if (splitPos[line] + maxChara - 2 < textLength)
			{
				splitPos.push_back(text.rfind(" ",(line==0)?(maxChara):(splitPos[line] + maxChara - 2)) + 1); //Text splits immediately after the space (+1)
			}
			else splitPos.push_back(textLength);

			for (int i = splitPos[line]; i < splitPos[line+1]; i++)
			{
				SDL_Surface* surface = TTF_RenderText_Blended(this->font, std::string(1, text[i]).c_str(), this->textColor);
				textureArray[i] = SDL_CreateTextureFromSurface(Game::renderer, surface);
				SDL_FreeSurface(surface);

				SDL_QueryTexture(textureArray[i], nullptr, nullptr, &tempPos.w, &tempPos.h);

				tempPos.w *= xscale;
				tempPos.h *= yscale;
				positionArray[i] = tempPos;
				tempPos.x += xscale*spacing;
			}

			tempPos.x = 2*xscale*spacing;
			tempPos.y += yscale*18;

			line++;
		}

		#pragma endregion

	}
	else refreshText(text);

	std::cout << line << std::endl;
}

void Text::refreshText(std::string text)
{
	SDL_DestroyTexture(texture);

	this->text = text;

	SDL_SetRenderTarget(Game::renderer, NULL);
	SDL_Surface* surface = TTF_RenderText_Blended(this->font, text.c_str(), this->textColor);
	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, nullptr, nullptr, &pos.w, &pos.h);

	trueWidth = pos.w;
	trueHeight = pos.h;
}

void Text::refreshOutline(void)
{
	if (simpleText)
	{
		static bool createdOutline = false;
		static SDL_Color previousColor = {outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a};
		static OutlineType previousType = outlineType;

		//Outside of if, so that if the text pos or scale change, the outline changes as well.
		outlinePos.x = pos.x - 1;
		outlinePos.y = pos.y - 0;
		outlinePos.w = trueWidth + 1;
		outlinePos.h = trueHeight + 1;

		if ((!createdOutline || outlineColor.r != previousColor.r || outlineColor.g != previousColor.g || outlineColor.b != previousColor.b || outlineColor.a != previousColor.a || outlineType != previousType || Game::getToggledFullscreen())&&(outlineColor.a))
		{
			//std::cout << "You so sussy, I know you took my outline!" << std::endl;

			if (outlineTexture != nullptr)
			{
				SDL_DestroyTexture(outlineTexture);
			}

			//Temporarily replaces the modified width and height with the true width and height in order to draw the outline
			int tempWidth = pos.w;
			int tempHeight = pos.h;

			outlineTexture = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, outlinePos.w, outlinePos.h);
			SDL_SetRenderTarget(Game::renderer, outlineTexture);
			SDL_SetTextureBlendMode(outlineTexture, SDL_BLENDMODE_BLEND);

			/*drawSetColor({255,0,0,255});
			SDL_RenderClear(Game::renderer);
			drawResetColor();*/

			if (outlineColor.a)
			{
				SDL_Color originColor = textColor;

				setColor(outlineColor);

				pos.w = trueWidth;
				pos.h = trueHeight;
				SDL_SetRenderTarget(Game::renderer, outlineTexture);

				pos.x -= outlinePos.x;
				pos.y -= outlinePos.y;

				pos.x-=1;
				if ((outlineType == full)||(outlineType == left_center)||(outlineType == discount))
					SDL_RenderCopy(Game::renderer, texture, nullptr, &pos); //Left center

				pos.y += 1;
				if ((outlineType == full)||(outlineType == left_bottom))
					SDL_RenderCopy(Game::renderer, texture, nullptr, &pos); //Left bottom

				pos.y -= 2;
				if ((outlineType == full)||(outlineType == left_top))
					SDL_RenderCopy(Game::renderer, texture, nullptr, &pos); //Left top

				pos.y += 1;
				pos.x+=2;
				if ((outlineType == full)||(outlineType == right_center)||(outlineType == discount))
					SDL_RenderCopy(Game::renderer, texture, nullptr, &pos); //Right center
				 
				pos.y += 1;
				if ((outlineType == full)||(outlineType == right_bottom))
					SDL_RenderCopy(Game::renderer, texture, nullptr, &pos); //Right bottom

				pos.y -= 2;
				if ((outlineType == full)||(outlineType == right_top))
					SDL_RenderCopy(Game::renderer, texture, nullptr, &pos); //Right top

				pos.x-=1;
				if ((outlineType == full)||(outlineType == center_top)||(outlineType == discount))
					SDL_RenderCopy(Game::renderer, texture, nullptr, &pos); //Center top

				pos.y += 2;
				if ((outlineType == full)||(outlineType == center_bottom)||(outlineType == discount))
					SDL_RenderCopy(Game::renderer, texture, nullptr, &pos); //Center bottom

				pos.y -= 1;
				setColor(originColor);

				SDL_SetRenderTarget(Game::renderer, outlineTexture);
				pos.w = trueWidth;
				pos.h = trueHeight;
				SDL_RenderCopy(Game::renderer, texture, nullptr, &pos);

				pos.x += outlinePos.x;
				pos.y += outlinePos.y;
			}

			createdOutline = true;
			previousColor = outlineColor;
			SDL_SetRenderTarget(Game::renderer, NULL);

			//Revert the width and height back to the modified values
			pos.w = tempWidth;
			pos.h = tempHeight;
		}

		outlinePos.w *= xscale;
		outlinePos.h *= yscale;
	}
}

void Text::setColor(SDL_Color color)
{
	textColor = color;
	refreshText(text);
}

void Text::setOutlineColor(SDL_Color color)
{
	outlineColor = color;
}

void Text::update(void)
{
	pos.w = trueWidth*xscale;
	pos.h = trueHeight*yscale;

	if (line > 3)
	{
		textboxPos.y = 5;
	}
	else textboxPos.y = 160 - 155*(Game::getPlayerPosInView());

	pos.x = textboxPos.x + xgap;
	pos.y = textboxPos.y + ygap;

	if (alarm == -1)
		alarm = 1;

	if (alarm == 0)
		alarm = 1;

	if (alarm - 1 >= 0)
		alarm--;

	//if (alarm >= 0)
		//std::cout << alarm <<std::endl;
}

void Text::draw(void)
{
	if (!simpleText)
	{
		if ((alarm == 0)&&(currentLetterIndex + 1 <= textLength))
		{
			currentLetterIndex++;
		}

		if (line > 3)
		{
			drawMenuBox(textboxPos.x, textboxPos.y, textboxPos.x + 289, textboxPos.y + 76 + 18*yscale*(line-3));
		}
		else drawMenuBox(textboxPos.x, textboxPos.y, textboxPos.x + 289, textboxPos.y + 76);

		for (int i = 0; i < currentLetterIndex; i++)
		{
			SDL_Rect tempPos = positionArray[i];
			tempPos.x += pos.x;
			tempPos.y += pos.y;

			//tempPos.x += (rand() % 2);
			//tempPos.y += (rand() % 2);

			SDL_RenderCopy(Game::renderer, textureArray[i], nullptr, &tempPos);
		}
	}
	else
	{
		refreshOutline();

		if (outlineColor.a != 0)
		{
			SDL_RenderCopy(Game::renderer, outlineTexture, nullptr, &outlinePos);
		}
		else SDL_RenderCopy(Game::renderer, texture, nullptr, &pos);
	}


	//SDL_QueryTexture(textureArray[2], nullptr, nullptr, &pos.w, &pos.h);
	//SDL_RenderCopy(Game::renderer, textureArray[2], nullptr, &pos);
}

Text::~Text(void)
{
	if (!simpleText)
	{
		for (int i = 0; i < textLength; i++)
		{
			SDL_DestroyTexture(textureArray[i]);
		}

		delete[] fontArray;
		delete[] textureArray;
		delete[] positionArray;
	}

	SDL_DestroyTexture(outlineTexture);
	SDL_DestroyTexture(texture);

	std::cout << "DESTROYED TEXT" << std::endl;
}

void Text::setScale(float xscale, float yscale)
{
	this->xscale = xscale;
	this->yscale = yscale;
}
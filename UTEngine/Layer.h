#pragma once
#include <iostream>
#include "json.hpp"
#include <vector>

class Layer
{
	private:
		std::vector<int> data;
		int height;
		int width;
		int x;
		int y;
		int opacity;
		bool visible;
		int id;
		std::string name;

	public:
		Layer(const nlohmann::json);
		Layer(const std::string, const int);
		int getX(void) const;
		int getY(void) const;
		int getWidth(void) const;
		int getHeight(void) const;
		int getOpacity(void) const;
		bool getVisible(void) const;
		int getId(void) const;
		std::string getName(void) const;
		std::vector<int> getData(void) const;
		int getTileAt(const int, const int) const;
		void printData(void) const;
		void printLayerInfo(void) const;
};
#include "Layer.h"
#include <iostream>
#include <iomanip>
#include "json.hpp"
#include "functions.h"

Layer::Layer(const nlohmann::json layer) //Creates a layer object from the layer array inside the .json file
{
	x = layer["x"];
	y = layer["y"];
	width = layer["width"];
	height = layer["height"];
	visible = layer["visible"];
	id = layer["id"];
	opacity = layer["opacity"];
	name = layer["name"];

	for(int i=0; i < width*height; i++)
	{
		data.push_back(layer["data"][i]);
	}
}

Layer::Layer(const std::string directory, const int layerNum)
{
	nlohmann::json layer = jsonLoad(directory)["layers"][layerNum];

	x = layer["x"];
	y = layer["y"];
	width = layer["width"];
	height = layer["height"];
	visible = layer["visible"];
	id = layer["id"];
	opacity = layer["opacity"];
	name = layer["name"];

	for(int i=0; i < width*height; i++)
	{
		data.push_back(layer["data"][i]);
	}
}

int Layer::getX(void) const
{
	return x;
}

int Layer::getY(void) const
{
	return y;
}

int Layer::getWidth(void) const
{
	return width;
}
int Layer::getHeight(void) const
{
	return height;
}

int Layer::getOpacity(void) const
{
	return opacity;
}

bool Layer::getVisible(void) const
{
	return visible;
}

int Layer::getId(void) const
{
	return id;
}

std::string Layer::getName(void) const
{
	return name;
}
std::vector<int> Layer::getData(void) const
{
	return data;
}

int Layer::getTileAt(const int row, const int column) const
{
	return data[row*width + column];
}

void Layer::printData(void) const
{
	std::cout<<"________________MAP________________"<<std::endl;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			std::cout << std::setw(5) << data[i*width+j];
		}

		std::cout<<std::endl;
	}
	std::cout<<"___________________________________"<<std::endl;
}

void Layer::printLayerInfo(void) const
{
	std::cout <<
		"____________LAYER INFO_____________\n"
		"Name: " << name <<
		"\nID: " << id <<
		"\nWidth: " << width <<
		"\nHeight: " << height <<
		"\nX: " << x <<
		"\nY: " << y <<
		"\nOpacity: " << opacity <<
		"\nVisible: " << visible <<
		"\n___________________________________" <<
	std::endl;
}
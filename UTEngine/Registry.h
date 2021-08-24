#pragma once
#include <map>
#include <iostream>
#include "SDL_ttf.h"

template <typename keyType, typename valueType>
class Registry
{
	private:
		std::map<keyType, valueType> reg; //For retrieval from key
		std::string name;
		std::vector<valueType> vec; //For existence checking and retrieval from index
		int values = 0;

	public:
		Registry(std::string name)
		{
			this->name = name;
		}
		
		void registration(keyType key, valueType value)
		{
			if (!exists(key))
			{
				reg.insert(std::pair<keyType, valueType>(key, value));
				vec.push_back(value);
				values++;
			}
			else std::cout << "Exists" << std::endl;
		}

		valueType get(int index)
		{
			return vec[index];
		}

		valueType operator[](keyType key)
		{
			return reg[key];
		}

		void print(void) const
		{
			std::cout << "==================== " + name + " ====================" << std::endl;
			for (std::pair<keyType, valueType> pair : reg)
			{
				std::cout << pair.first << std::endl;
			}
		}

		void printOrdered(void) const
		{
			std::cout << "==================== " + name + " (ORDERED) ====================" << std::endl;
			for (const valueType& x : vec)
			{
				std::cout << *x << std::endl;
			}
		}

		bool exists(keyType key) const
		{
			return reg.count(key);
		}

		int size(void) const
		{
			return values;
		}
};

/*
//Specialization for fonts, because I'm a fucking idiot
template <typename T>
class Registry<T, TTF_Font*>
{
	private:
		std::map<T, TTF_Font*> reg;
		std::string name;
		std::vector<TTF_Font*> vec;
		int values = 0;

	public:
		Registry(std::string name)
		{
			this->name = name;
		}

		~Registry(void)
		{
			for (auto font : vec)
				TTF_CloseFont(font);

			std::cout << "Deleted Font Registry" << std::endl;
			vec.clear();
		}
		
		void registration(T key, TTF_Font* value)
		{
			if (!exists(key))
			{
				reg.insert(std::pair<T, TTF_Font*>(key, value));
				vec.push_back(value);
				values++;
			}
			else std::cout << "Exists" << std::endl;
		}

		TTF_Font* get(int index)
		{
			return vec[index];
		}

		TTF_Font* operator[](T key)
		{
			return reg[key];
		}

		void print(void) const
		{
			std::cout << "==================== " + name + " ====================" << std::endl;
			for (std::pair<T, TTF_Font*> pair : reg)
			{
				std::cout << pair.first << std::endl;
			}
		}

		void printOrdered(void) const
		{
			std::cout << "==================== " + name + " (ORDERED) ====================" << std::endl;
			for (auto x : vec)
			{
				std::cout << *x << std::endl;
			}
		}

		bool exists(T key) const
		{
			return reg.count(key);
		}

		int size(void) const
		{
			return values;
		}
};*/
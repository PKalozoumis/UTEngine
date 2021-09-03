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
		std::vector<valueType> vec; //For existence checking and retrieval from index. Items are ordered
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
				//reg.insert(std::pair<keyType, valueType>(key, value));
				reg.insert(std::map<keyType, valueType>::value_type(key, value));
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
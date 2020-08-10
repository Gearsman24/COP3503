#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>

class Textures
{
	static std::unordered_map<std::string, sf::Texture> textures;

public:
	static void LoadTexture(const char* file);
	static sf::Texture& getTexture(const char* name);
	static void Clear();
};


#include "Textures.h"

std::unordered_map<std::string, sf::Texture> Textures::textures;

void Textures::LoadTexture(const char* file)
{
	std::string filePath = "images\\";
	filePath += file;
	filePath += ".png";

	textures[file].loadFromFile(filePath);
}

sf::Texture& Textures::getTexture(const char* name)
{
	if (textures.find(name) == textures.end())
	{
		LoadTexture(name);
	}

	return textures[name];
}

void Textures::Clear()
{
	textures.clear();
}
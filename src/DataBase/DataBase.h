#pragma once

#include <array>
#include <unordered_map>
#include "Utils/CopyInhertance.h"

#include "ID.h"
#include "World/Blocks/Block.h"
#include "Item/Material/Material.h"
#include "Item/Item/Item.h"

#include "SFML/Graphics.hpp"

class Application;

class DataBase : public Singleton {
public:
	static DataBase & get(Application* app = nullptr);
	DataBase& Init();

	Block&		getBlock(const ID& id);
	Material&	getMaterial(const MID & id);
	Item&		getItem(const ItID& id);
	sf::Texture getTexture(const std::string& s);

	sf::Text&	getText();
private:
	DataBase(Application* app);

	sf::Text text;
	sf::Font font;

	std::unordered_map<std::string, sf::Texture>					Textures;
	std::array<std::unique_ptr<Block>,		(unsigned)ID::NUM>		blocks;
	std::array<std::unique_ptr<Material>,	(unsigned)MID::NUM>		materials;
	std::array<std::unique_ptr<Item>,		(unsigned)ItID::NUM>	items;
};



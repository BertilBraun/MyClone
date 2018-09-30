#include "DataBase.h"
#include "Application.h"

DataBase & DataBase::get(Application* app) {
	static bool hasInit = false;
	static DataBase db(app); 
	if (app != nullptr)
		db.text.setCharacterSize((*app->getWindow()).getSize().y / 40);
	if (!hasInit) {
		hasInit = true;
		db.Init();
	}
	return db; 
}

DataBase & DataBase::Init() {
	for (auto& b : blocks)
		b->Init();
	return *this;
}

Block & DataBase::getBlock(const ID & id) {
	if (id < ID::Air || id >= ID::NUM)
		throw std::runtime_error("THIS ID DOESNT REPRESENT A BLOCK" + std::to_string((int)id));
	return *blocks[(unsigned)id];
}

Material & DataBase::getMaterial(const MID & id) {
	if ((int)id < 0 || id >= MID::NUM)
		throw std::runtime_error("THIS ID DOESNT REPRESENT A MATERIAL" + std::to_string((int)id));
	return *materials[(unsigned)id];
}

Item & DataBase::getItem(const ItID & id) {
	if ((int)id < 0 || id >= ItID::NUM)
		throw std::runtime_error("THIS ID DOESNT REPRESENT A ITEM" + std::to_string((int)id));
	return *items[(unsigned)id];
}

sf::Texture DataBase::getTexture(const std::string & s) {

	if (Textures.find(s) != Textures.end())
		return Textures[s];
	return sf::Texture();
}

sf::Text & DataBase::getText()
{
	return text;
}

DataBase::DataBase(Application* app) {

	blocks[(int)ID::Air			] = std::make_unique<Block>("Air");
	blocks[(int)ID::Grass		] = std::make_unique<Block>("Grass");
	blocks[(int)ID::Dirt		] = std::make_unique<Block>("Dirt");
	blocks[(int)ID::Stone		] = std::make_unique<Block>("Stone");
	blocks[(int)ID::Wood		] = std::make_unique<Block>("Wood");
	blocks[(int)ID::Leave		] = std::make_unique<Block>("Leave");
	blocks[(int)ID::Sand		] = std::make_unique<Block>("Sand");
	blocks[(int)ID::Cobble		] = std::make_unique<Block>("Cobble");
	blocks[(int)ID::Water		] = std::make_unique<Block>("Water");
	blocks[(int)ID::Cactus		] = std::make_unique<Block>("Cactus");
	blocks[(int)ID::Gravel		] = std::make_unique<Block>("Gravel");
	blocks[(int)ID::ShortGrass	] = std::make_unique<Block>("ShortGrass");
	blocks[(int)ID::Rose		] = std::make_unique<Block>("Rose");
	blocks[(int)ID::DeadBush	] = std::make_unique<Block>("DeadBush");
	blocks[(int)ID::Plank		] = std::make_unique<Block>("Plank");
	blocks[(int)ID::Iron		] = std::make_unique<Block>("Iron");
	blocks[(int)ID::SnowGrass	] = std::make_unique<Block>("SnowGrass");
	blocks[(int)ID::Fern		] = std::make_unique<Block>("Fern");
	blocks[(int)ID::PineWood	] = std::make_unique<Block>("PineWood");
	blocks[(int)ID::PineLeave	] = std::make_unique<Block>("PineLeave");
	blocks[(int)ID::Glass		] = std::make_unique<Block>("Glass");

	materials[(int)MID::COAL	] = std::make_unique<Material>("Coal");
	materials[(int)MID::IRON	] = std::make_unique<Material>("Iron");

	items[(int)ItID::AXE		] = std::make_unique<Item>("Axe");
	
	Textures["Axe"				].loadFromFile("res/Textures/ResourcePacks/InvTextures/Axe.png");
	Textures["Iron"				].loadFromFile("res/Textures/ResourcePacks/InvTextures/Iron.png");

	Textures["Transparent"		].loadFromFile("res/Textures/GUI/Transparent.png");
	Textures["Button"			].loadFromFile("res/Textures/GUI/Button.png");
	Textures["HoverButton"		].loadFromFile("res/Textures/GUI/HoverButton.png");
	Textures["health"			].loadFromFile("res/Textures/GUI/health.png");
	Textures["noHealth"			].loadFromFile("res/Textures/GUI/noHealth.png");

	
	font.loadFromFile("res/Textures/Fonts/rs.ttf");

	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1);

	text.setFont(font);
	text.setCharacterSize(20);
}

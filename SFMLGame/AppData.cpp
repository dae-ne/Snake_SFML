#include "AppData.h"

RiA::AppData* RiA::AppData::pInstance = NULL;

void RiA::AppData::Init(sf::RenderWindow& window)
{
	if (!pInstance)
		pInstance = new AppData();

	pInstance->pWindow = &window;

	try
	{
		pInstance->loadFontsFromFile();
	}
	catch(std::exception& e)
	{
		MessageBox(NULL, e.what(), NULL, MB_OK);
	}
}

RiA::AppData& RiA::AppData::GetData()
{
	if (!pInstance)
		pInstance = new AppData();

	return *pInstance;
}

void RiA::AppData::Remove()
{
	if (pInstance)
		delete pInstance;

	pInstance = NULL;
}

void RiA::AppData::setUpdateTime(DifficultyLevel difficultyLevel)
{
	switch (difficultyLevel)
	{
	case DifficultyLevel::Easy:
		updateTime = 200;
		break;

	case DifficultyLevel::Normal:
		updateTime = 100;
		break;

	case DifficultyLevel::Hard:
		updateTime = 50;
		break;
	}
}

RiA::AppData::AppData()
{
	pWindow = NULL;
	difficultyLevel = DifficultyLevel::Normal;
	setUpdateTime(DifficultyLevel::Normal);
}

void RiA::AppData::loadFontsFromFile()
{
	sf::Font font;
	std::string folderName = "Fonts/";
	std::string fontNames[] = {
		"Hardcore.otf",
		"28 Days Later.ttf"
	};

	for (auto name : fontNames)
	{
		if (!font.loadFromFile(folderName + name))
			throw std::runtime_error(folderName + name + " not found!!!");

		fonts.push_back(font);
	}
}

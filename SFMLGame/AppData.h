#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <Windows.h>

#define MainFont 0
#define ButtonFont 1
#define SaveFileDirectory "Saves/save.txt"

enum class DifficultyLevel
{
	Easy = 0,
	Normal,
	Hard
};

namespace RiA
{
	class AppData
	{
	public:
		static void Init(sf::RenderWindow& window);
		static AppData& GetData();
		static void Remove();

		sf::RenderWindow& getWindow() { return *pWindow; }
		sf::Font& getFont(int whichOne) { return fonts[whichOne]; }

		std::vector<sf::Event>& getEvents() { return events; }
		void addEvent(sf::Event& event) { events.push_back(event); }
		void removeEventList() { events.clear(); }

		DifficultyLevel getDifficultyLevel() { return difficultyLevel; }
		std::string getDifficultyLevelAsString() { return difficultyLevel_str[(int)difficultyLevel]; }
		void setDifficultyLevel(DifficultyLevel newDifficultyLevel) { difficultyLevel = newDifficultyLevel; }

		void setUpdateTime(DifficultyLevel difficultyLevel);
		sf::Int32 getUpdateTime() { return updateTime; }

	private:
		AppData();

		void loadFontsFromFile();

	private:
		static AppData* pInstance;

		sf::RenderWindow* pWindow;
		std::vector<sf::Font> fonts;
		std::vector<sf::Event> events;

		DifficultyLevel difficultyLevel;

		const std::string difficultyLevel_str[3] = {
			"Easy",
			"Normal",
			"Hard"
		};

		sf::Int32 updateTime;
	};
}
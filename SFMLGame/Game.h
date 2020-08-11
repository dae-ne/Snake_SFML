#pragma once
#include "IState.h"
#include "AppData.h"
#include <vector>

#define RECT_SIZE 20

namespace RiA
{
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	//===================================================================

	class Snake : public sf::Drawable
	{
		friend class Collision;
		friend class SaveFile;

	public:
		Snake();

		void increaseLength();
		void move();

		void setDirection(Direction dir) { direction = dir; }
		Direction getDirection() { return direction2; }

	private:
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		
	private:
		std::vector<sf::RectangleShape> vec;
		Direction direction;
		Direction direction2;
	};

	//===================================================================

	class Food : public sf::Drawable
	{
		friend class Collision;
		friend class SaveFile;

	public:
		Food();

		void newRandomPosition();

	private:
		void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		sf::RectangleShape rectangle;
	};

	//===================================================================

	class Stats : public sf::Drawable
	{
		friend class SaveFile;

	public:
		Stats();

		void addPoint() { points++; }
		void update(bool gamePaused);

	private:
		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void textInit();

	private:
		unsigned points;
		sf::Clock clock;
		float time;
		sf::Text points_text;
		sf::Text time_text;
	};

	//===================================================================

	class Game : public IState
	{
	public:
		Game(bool continueGame = false);
		~Game();

		void control() override;
		void update() override;
		void draw() override;

	private:
		Snake snake;
		Food food;
		Stats stats;

		bool isGamePaused;
		bool crash;
	};

	//===================================================================

	class Collision
	{
	public:
		static bool SnakeWithWall(Snake&);
		static bool SnakeWithFood_HeadOnly(Snake&, Food&);
		static bool SnakeWithFood(Snake&, Food&);

	private:
		Collision() = default;
	};

	//===================================================================

	class SaveFile
	{
	public:
		static void SaveToFile(Snake& snake, Food& food, Stats& stats);
		static void LoadFromFile(Snake& snake, Food& food, Stats& stats);

	private:
		SaveFile() = default;
	};
}
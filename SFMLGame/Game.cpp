#include "Game.h"
#include <cstdio>
#include <string>
#include <fstream>
#include <Windows.h>

RiA::Snake::Snake()
{
	sf::RectangleShape head({ RECT_SIZE, RECT_SIZE });
	head.setPosition(0, 0);
	direction = Direction::Right;
	direction2 = direction;

	vec.push_back(head);
}

void RiA::Snake::increaseLength()
{
	vec.push_back(vec[vec.size() - 1]);
	vec[vec.size() - 1].move(0.0001f, 0);
}

void RiA::Snake::move()
{
	sf::Vector2f position[2];
	position[0] = vec[0].getPosition();
	bool flag = false;

	switch (direction)
	{
	case Direction::Up:
		vec[0].move(0, -RECT_SIZE);
		break;

	case Direction::Down:
		vec[0].move(0, RECT_SIZE);
		break;

	case Direction::Left:
		vec[0].move(-RECT_SIZE, 0);
		break;

	case Direction::Right:
		vec[0].move(RECT_SIZE, 0);
		break;
	}

	for (size_t i = 1; i < vec.size(); i++)
	{
		position[!flag] = vec[i].getPosition();
		vec[i].setPosition(position[flag]);
		flag = !flag;
	}

	direction2 = direction;
}

void RiA::Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto rect : vec)
		target.draw(rect);
}

RiA::Food::Food()
{
	srand((unsigned)time(NULL));
	rectangle.setSize({ RECT_SIZE, RECT_SIZE });
}

void RiA::Food::newRandomPosition()
{
	sf::Vector2f newPosition;
	sf::Vector2i gameSize;
	gameSize.x = AppData::GetData().getWindow().getSize().x / RECT_SIZE;
	gameSize.y = AppData::GetData().getWindow().getSize().y / RECT_SIZE;

	newPosition.x = (float)((rand() % gameSize.x) * RECT_SIZE);
	newPosition.y = (float)((rand() % gameSize.y) * RECT_SIZE);

	rectangle.setPosition(newPosition);
}

void RiA::Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rectangle);
}

RiA::Game::Game(bool continueGame)
{
	AppData::GetData().getWindow().setMouseCursorVisible(false);
	isGamePaused = true;
	crash = false;

	if (!continueGame)
	{
		do
		{
			food.newRandomPosition();
		} while (Collision::SnakeWithFood(snake, food));
	}

	else SaveFile::LoadFromFile(snake, food, stats);
}

RiA::Game::~Game()
{
	AppData::GetData().getWindow().setMouseCursorVisible(true);
	SaveFile::SaveToFile(snake, food, stats);

	if (crash)
		std::remove("Saves/save.txt");
}

void RiA::Game::control()
{
	std::vector<sf::Event> events = AppData::GetData().getEvents();

	for (auto event : events)
	{
		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Space)
			isGamePaused = !isGamePaused;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		setState(State::MainMenu);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (snake.getDirection() != Direction::Down)
			snake.setDirection(Direction::Up);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (snake.getDirection() != Direction::Up)
			snake.setDirection(Direction::Down);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		if (snake.getDirection() != Direction::Right)
			snake.setDirection(Direction::Left);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		if (snake.getDirection() != Direction::Left)
			snake.setDirection(Direction::Right);
	}
}

void RiA::Game::update()
{
	static sf::Clock clock;

	if (clock.getElapsedTime().asMilliseconds() >= AppData::GetData().getUpdateTime())
	{
		if (!isGamePaused)
			snake.move();

		clock.restart();
	}

	if (Collision::SnakeWithWall(snake))
	{
		setState(State::MainMenu);
		crash = true;
	}

	if (Collision::SnakeWithFood_HeadOnly(snake, food))
	{
		snake.increaseLength();
		stats.addPoint();

		do
		{
			food.newRandomPosition();
		} while (Collision::SnakeWithFood(snake, food));
	}

	stats.update(isGamePaused);
}

void RiA::Game::draw()
{
	AppData::GetData().getWindow().draw(food);
	AppData::GetData().getWindow().draw(snake);
	AppData::GetData().getWindow().draw(stats);
}

bool RiA::Collision::SnakeWithWall(Snake& snake)
{
	if (snake.vec[0].getPosition().x < 0 ||
		snake.vec[0].getPosition().x > AppData::GetData().getWindow().getSize().x - RECT_SIZE ||
		snake.vec[0].getPosition().y < 0 ||
		snake.vec[0].getPosition().y > AppData::GetData().getWindow().getSize().y - RECT_SIZE)
		return true;

	for (size_t i = 1; i < snake.vec.size(); i++)
	{
		if (snake.vec[0].getPosition() == snake.vec[i].getPosition())
			return true;
	}

	return false;
}

bool RiA::Collision::SnakeWithFood_HeadOnly(Snake& snake, Food& food)
{
	if (snake.vec[0].getPosition() == food.rectangle.getPosition())
		return true;

	return false;
}

bool RiA::Collision::SnakeWithFood(Snake& snake, Food& food)
{
	for (auto snakeSegment : snake.vec)
	{
		if (snakeSegment.getPosition() == food.rectangle.getPosition())
			return true;
	}

	return false;
}

RiA::Stats::Stats()
{
	points = 0;
	time = 0;
	textInit();
}

void RiA::Stats::update(bool gamePaused)
{
	if (!gamePaused)
		time += clock.getElapsedTime().asSeconds();

	clock.restart();

	points_text.setString("Points: " + std::to_string(points));
	time_text.setString("Time: " + std::to_string((int)time));
}

void RiA::Stats::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(points_text);
	target.draw(time_text);
}

void RiA::Stats::textInit()
{
	const unsigned characterSize = 60;
	sf::Vector2f position(0, (float)(AppData::GetData().getWindow().getSize().y - characterSize));

	points_text.setString("Points: 0");
	points_text.setFont(AppData::GetData().getFont(MainFont));
	points_text.setCharacterSize(characterSize);
	points_text.setFillColor(sf::Color::Magenta);
	points_text.setOrigin(0, points_text.getGlobalBounds().height);
	points_text.setPosition(position);

	time_text.setString("Time: 0");
	time_text.setFont(AppData::GetData().getFont(MainFont));
	time_text.setCharacterSize(characterSize);
	time_text.setFillColor(sf::Color::Magenta);
	time_text.setPosition(position);
}

void RiA::SaveFile::SaveToFile(Snake& snake, Food& food, Stats& stats)
{
	std::ofstream file(SaveFileDirectory);

	if (file.is_open())
	{		
		for (auto snakeSegment : snake.vec)
		{
			file << snakeSegment.getPosition().x << ' '
				<< snakeSegment.getPosition().y << ' ';
		}

		file << food.rectangle.getPosition().x << ' '
			<< food.rectangle.getPosition().y << ' ';

		int dir = 0;

		switch (snake.direction2)
		{
		case Direction::Up:
			dir = 0;
			break;

		case Direction::Down:
			dir = 1;
			break;

		case Direction::Left:
			dir = 2;
			break;

		case Direction::Right:
			dir = 3;
			break;
		}

		file << dir << ' ' << stats.time;

		file.close();
	}

	else MessageBox(NULL, "Cannot open file!!!", NULL, MB_OK);
}

void RiA::SaveFile::LoadFromFile(Snake& snake, Food& food, Stats& stats)
{
	std::string str;
	std::vector<std::string> data;
	std::ifstream file(SaveFileDirectory);

	if (file.is_open())
	{
		while (file >> str)
			data.push_back(str);

		file.close();
	}

	else MessageBox(NULL, "Cannot open file!!!", NULL, MB_OK);

	stats.time = std::stof(data[data.size() - 1]);
	data.pop_back();

	int dir = std::stoi(data[data.size() - 1]);
	data.pop_back();

	switch (dir)
	{
	case 0:
		snake.direction = Direction::Up;
		snake.direction2 = Direction::Up;
		break;

	case 1:
		snake.direction = Direction::Down;
		snake.direction2 = Direction::Down;
		break;

	case 2:
		snake.direction = Direction::Left;
		snake.direction2 = Direction::Left;
		break;

	case 3:
		snake.direction = Direction::Right;
		snake.direction2 = Direction::Right;
		break;
	}

	food.rectangle.setPosition(std::stof(data[data.size() - 2]), std::stof(data[data.size() - 1]));

	data.pop_back();
	data.pop_back();

	snake.vec[0].setPosition(std::stof(data[0]), std::stof(data[1]));

	for (unsigned i = 2; i < data.size(); i += 2)
	{
		sf::RectangleShape rectangle({ RECT_SIZE, RECT_SIZE });
		rectangle.setPosition(std::stof(data[i]), std::stof(data[i + 1]));
		snake.vec.push_back(rectangle);
	}

	stats.points = snake.vec.size() - 1;
}
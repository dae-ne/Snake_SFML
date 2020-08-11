#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AppData.h"
#include <vector>

namespace RiA
{
	class Application
	{
	public:
		static void Run();
		static void Terminate();

	private:
		Application();
		~Application();

		void mainLoop();
		void events();

		void control(IState*);
		void update(IState*);
		void drawScene(IState*);

	private:
		static Application* pInstance;
		sf::RenderWindow window;
		IState* pState;
	};
}
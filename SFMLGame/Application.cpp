#include "Application.h"

RiA::Application* RiA::Application::pInstance = NULL;

RiA::Application::Application()
{
	AppData::Init(window);
	window.create(sf::VideoMode(800, 600), "SFML window", sf::Style::Close);

	pState = NULL;
}

RiA::Application::~Application()
{
	AppData::Remove();
}

void RiA::Application::mainLoop()
{
	StateMachine stateMachine(State::MainMenu);

	while (window.isOpen())
	{
		pState = stateMachine.switchStates();

		control(pState);
		update(pState);
		drawScene(pState);
	}
}

void RiA::Application::events()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			pState->setState(State::ExitMenu);

		AppData::GetData().addEvent(event);
	}
}

void RiA::Application::control(IState* pState)
{
	events();
	pState->control();
	AppData::GetData().removeEventList();
}

void RiA::Application::update(IState* pState)
{
	pState->update();
}

void RiA::Application::drawScene(IState* pState)
{
	window.clear();
	pState->draw();
	window.display();
}

void RiA::Application::Run()
{
	if (!pInstance)
		pInstance = new Application();

	pInstance->mainLoop();
}

void RiA::Application::Terminate()
{
	if (pInstance)
		delete pInstance;

	pInstance = NULL;
}

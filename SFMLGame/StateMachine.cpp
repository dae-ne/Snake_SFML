#include "StateMachine.h"

RiA::StateMachine::StateMachine(State state)
{
	pState = NULL;
	this->state = state;
}

RiA::StateMachine::~StateMachine()
{
	deleteState();
}

RiA::IState* RiA::StateMachine::switchStates()
{
	do
	{
		if (!pState)
		{
			switch (state)
			{
			case State::MainMenu:
				pState = new MainMenu();
				break;

			case State::SettingsMenu:
				pState = new SettingsMenu();
				break;

			case State::ExitMenu:
				pState = new ExitMenu();
				break;

			case State::Game:
				pState = new Game();
				break;

			case State::GameContinue:
				pState = new Game(true);
				break;
			}

			pState->setState(state);
		}
		else
		{
			State currentState = pState->getState();

			if (currentState != state)
			{
				deleteState();
				state = currentState;
			}
		}
	}
	while (!pState);

	return pState;
}

void RiA::StateMachine::deleteState()
{
	if (pState)
		delete pState;

	pState = NULL;
}

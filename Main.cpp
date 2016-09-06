//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
// Description: This is the entry point for any game using the SDL Game Engine
//////////////////////////////////////////////////////////////////////////////////

#include "Defines.h"
#include "cGraphics.h"
#include "cInput.h"
#include "cStateManager.h"
#include <iostream>

// Note that the parameters and return type here are required by SDL, 
// even though you'll probably never use them. 
int main(int argc, char **argv)
{
	//cGraphics* graphics = new cGraphics(WINDOW_WIDTH, WINDOW_HEIGHT,
	//	WINDOW_TITLE); 
	cGraphics* graphics = new cGraphics(EDITOR_WIDTH, EDITOR_HEIGHT,
		EDITOR_TITLE); 
	cInput* input = new cInput();

	cStateManager* stateManager =new cStateManager(graphics, input);

	// This is the game loop. It continues until the current state's Run()
	// method returns false. State changes are handled by the state manager.
	while ( stateManager->CurrentState()->Run(stateManager) ) {}

	delete input;
	delete graphics;

	return 0;
}
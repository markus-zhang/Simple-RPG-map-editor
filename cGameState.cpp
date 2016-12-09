#include "cGameState.h"
#include "cStateManager.h"
#include "Math.h"
#include <iostream>
#include <fstream>

cGameState::cGameState(cGraphics* graphics, cInput* input) :
	cState(graphics, input) {
	m_Tilemap = m_Graphics->LoadTexture("Tileset.png",
		255, 255, 255);
	m_PlayerSprite = m_Graphics->LoadTexture("./Resource/Animation.png",
		255, 255, 255);
	m_PlayerSprite == NULL ? DebugMessage("Player Sprite NULL!") : DebugMessage("Player Sprite successfully loaded");
	//m_FileManager.LoadEntityTest("./Resource/entity.setting", m_Test, m_Graphics, m_TestSprite);

	//SetBias(m_World[m_CurrentLevel].GetXBias(), m_World[m_CurrentLevel].GetYBias());

	//Load World
	m_FileManager.LoadWorld("world.setting", m_Graphics, m_Tilemap, m_World);
	m_CurrentLevel = 0;

	//Load Player
	m_Player = m_FileManager.ReturnSingleEntityTest(
		"./Resource/entity.player.setting", m_Graphics,
		m_PlayerSprite);

	//m_Cursor = m_Graphics->LoadTexture("cursor.png", 255, 255, 255);
	//m_ButtonPic = m_Graphics->LoadTexture("GUIButton.png", 255, 255, 255);
	//m_EntityPic = m_Graphics->LoadTexture("Entity.png", 0, 0, 0);
	//m_TestPic = m_Graphics->LoadTexture("BasicButtonBackground.png", 255, 255, 255);
	//m_Painter = cCursor(m_Graphics, m_Cursor, EDITOR_MOUSE_X_START,
		//EDITOR_MOUSE_Y_START,
		//EDITOR_CURSOR_WIDTH, EDITOR_CURSOR_HEIGHT);
	//m_Mode = Mode_Tile;

	//Test Inventory
	//m_FileManager.LoadInventoryFromFile("item.txt", m_Inventory);
	//vector<cItem>::iterator it;
	//for (it = m_Inventory.begin(); it != m_Inventory.end(); it++) {
	//(*it).Dump();
	//}
	//m_TitleTest = new cScrollTitle(m_Graphics);
	//m_TitleTest->PreprocessText();
	//m_TitleTest->PreprocessPara();
	//m_TitleTest->Dump();

	// Experimental
		//m_FileManager.LoadDMLObject();
		//std::string test = "     <name> Gobli n</name>";
		//m_FileManager.RemoveSpace(test);
	// Experimental end
}

cGameState::~cGameState() {

}

bool cGameState::Run(cStateManager* state_manager)
{
	static int last_tick = SDL_GetTicks();
	int this_tick = SDL_GetTicks();

	//If still in the same tick, sleep 
	if (this_tick <= last_tick)
	{
		SDL_Delay(1);
		return  m_IsRunning;
	}

	while (last_tick < this_tick)
	{
		HandleInput(state_manager);
		last_tick += 1000 / PHYSICS_FPS;
	}
	m_World[m_CurrentLevel].Update();
	m_Player.SetLocation(m_World[m_CurrentLevel].GetX(), m_World[m_CurrentLevel].GetY());
	m_Player.Update();

	//Clear the screen before every frame
	m_Graphics->ClearScreen();

	m_World[m_CurrentLevel].Draw();

	// Test
	m_Player.PlayAnimationBiased("IDLE", 
		m_World[m_CurrentLevel].GetXBias(), 
		m_World[m_CurrentLevel].GetYBias());

	m_Graphics->Show();

	return m_IsRunning;
}

void cGameState::HandleInput(cStateManager* state_manager)
{
	// Make sure a new event has happened and handle key presses 
	if (m_Input->GetEvent())
	{
		// Handle user manually closing game window 
		if (m_Input->IsQuit())
		{
			m_IsRunning = false;
			return;  // game is over, exit the method
		}

		// Handle keyboard input here (keys being held down are handled below)
		switch (m_Input->GetKeyPressed())
		{
			/*case SDLK_ESCAPE:
			{
			state_manager->ChangeState(State_Menu);
			} break;*/

		case SDL_SCANCODE_UP: {
			m_World[m_CurrentLevel].GetY() >= m_World[m_CurrentLevel].GetMapNorthBorder() + 32 ? m_World[m_CurrentLevel].SetY(-32) : DebugMessage("Cannot move north!");
			std::cout << m_World[m_CurrentLevel].GetX() << " " << m_World[m_CurrentLevel].GetY() << "\n";
		}break;
		case SDL_SCANCODE_DOWN: {
			m_World[m_CurrentLevel].GetY() <= m_World[m_CurrentLevel].GetMapSouthBorder() - 32 ? m_World[m_CurrentLevel].SetY(32) : DebugMessage("Cannot move south!");
			std::cout << m_World[m_CurrentLevel].GetX() << " " << m_World[m_CurrentLevel].GetY() << "\n";
		}break;
		case SDL_SCANCODE_LEFT: {
			m_World[m_CurrentLevel].GetX() >= m_World[m_CurrentLevel].GetMapWestBorder() + 32 ? m_World[m_CurrentLevel].SetX(-32) : DebugMessage("Cannot move west!");
			std::cout << m_World[m_CurrentLevel].GetX() << " " << m_World[m_CurrentLevel].GetY() << "\n";
		}break;
		case SDL_SCANCODE_RIGHT: {
			m_World[m_CurrentLevel].GetX() <= m_World[m_CurrentLevel].GetMapEastBorder() - 32 ? m_World[m_CurrentLevel].SetX(32) : DebugMessage("Cannot move east!");
			std::cout << m_World[m_CurrentLevel].GetX() << " " << m_World[m_CurrentLevel].GetY() << "\n";
		}break;

		}
	}
}

void cGameState::SetBias(int xbias, int ybias)
{
	m_XBias = xbias;
	m_YBias = ybias;
}
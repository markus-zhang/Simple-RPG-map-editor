//#include "cEditorState0908.h"
//#include "cStateManager.h"
//#include "Math.h"
//#include <iostream>
//#include <fstream>
//
//cEditorState::cEditorState(cGraphics* graphics, cInput* input) : 
//											cState(graphics, input)
//{
//	m_Tilemap = m_Graphics->LoadTexture("Tileset.png",
//										255, 255, 255);
//	m_Cursor = m_Graphics->LoadTexture("cursor.png", 255, 255, 255);
//	m_ButtonPic = m_Graphics->LoadTexture("GUIButton.png", 255, 255, 255);
//	m_EntityPic = m_Graphics->LoadTexture("Entity.png", 0, 0, 0);
//
//	m_Painter = cCursor(m_Graphics, m_Cursor, EDITOR_MOUSE_X_START,
//						EDITOR_MOUSE_Y_START, 
//						EDITOR_CURSOR_WIDTH, EDITOR_CURSOR_HEIGHT);
//	m_Mode = Mode_Tile;
//
//	// Load Buttons
//	m_FileManager.LoadGeneralButton("gui.ini", m_Graphics, m_ButtonPic,
//									"gui", m_GUI);
//	m_FileManager.LoadGeneralButton("guitexture.ini", m_Graphics, m_Tilemap,
//									"tile", m_GUI);
//	m_FileManager.LoadEntityButton("entity.ini", m_Graphics, m_EntityPic,
//									m_GUI);
//	m_Enemy.OpenDB("enemy.db");
//	m_Enemy.GetIndex("IdIndexEnemy");
//	m_Enemy.GetValueByDoubleIndex("ID", "0Cleric", "HP", "Enemy");
//
//	m_XBias = 0;
//	m_YBias = 0;	// Initially there is no bias
//}
//
//cEditorState::~cEditorState() {}
//
//bool cEditorState::Run(cStateManager* state_manager)
//{
//	static int last_tick = SDL_GetTicks();
//  	int this_tick = SDL_GetTicks();
//
//	if (this_tick <= last_tick) 
//	{
//		SDL_Delay(1);
//		return  m_IsRunning;
//	}
//
//	while (last_tick < this_tick)
//	{
//		HandleInput(state_manager);
//		last_tick += 1000 / PHYSICS_FPS;
//	}
//
//	//Clear the screen before every frame
//	m_Graphics->ClearScreen();
//
//	BlinkTile();
//
//	for (size_t i=0; i<m_MapVector.size(); i++)
//	{
//		m_MapVector[i].DrawBias(m_XBias, m_YBias);
//	}
//
//	for (size_t i=0; i<m_EntityVector.size(); i++)
//	{
//		m_EntityVector[i].SetCurrentFrame();
//		m_EntityVector[i].DrawBias(m_XBias, m_YBias);
//	}
//
//	m_GUI.Draw();
//
//	m_Painter.Draw();
//
//	m_Graphics->Show();
//
//	return m_IsRunning;
//}
//
//void cEditorState::HandleInput(cStateManager* state_manager)
//{
//	// Make sure a new event has happened and handle key presses 
//	if (m_Input->GetEvent()) 
//	{
//		// Handle user manually closing game window 
//		if ( m_Input->IsQuit() )
//		{			
//			m_IsRunning = false;
//
//			return;  // game is over, exit the method
//		}
//		// Handle keyboard input here (keys being held down are handled below)
//		switch (m_Input->GetKeyPressed())
//		{
//			/*case SDLK_ESCAPE:
//			{
//				state_manager->ChangeState(State_Menu);			
//			} break;*/
//
//			case SDL_SCANCODE_LEFT:
//			{
//				if (m_Painter.CanMoveLeft()) m_Painter.MoveLeft();
//			} break;
//
//
//			case SDL_SCANCODE_RIGHT:
//			{
//				if (m_Painter.CanMoveRight()) m_Painter.MoveRight();
//			} break;
//			
//			case SDL_SCANCODE_UP:
//			{
//				if (m_Painter.CanMoveUp()) m_Painter.MoveUp();
//			} break;
//
//
//			case SDL_SCANCODE_DOWN:
//			{
//				if (m_Painter.CanMoveDown()) m_Painter.MoveDown();
//			} break;
//
//			case SDL_SCANCODE_D:
//			{
//				DumpMap();
//			} break;
//
//			// Delete tile
//			case SDL_SCANCODE_DELETE:
//			{
//				if (m_MapVector.size() > 0)
//				{
//					m_MapStack.push_back(m_MapVector);		// Save current state
//					cout << "Old state saved " << m_MapStack.size() <<"\n";
//				}
//				RemoveTile();
//			} break;
//
//			// Undo
//			case SDL_SCANCODE_U:
//			{
//				if (m_MapStack.size() == 0)
//				{
//					cout << "Cannot Undo." << "\n";
//					break;
//				}
//				cout << "Undo" << "\n";
//				m_MapVector = m_MapStack.back();
//				m_MapStack.pop_back();
//			} break;
//
//			case SDL_SCANCODE_S:
//			{
//				//Save Map
//				
//				m_MapData.SaveMap("map1.txt", m_MapVector);
//				//Save Entity
//				m_EntityData.SaveEntity("entity.sav", m_EntityVector);
//			} break;
//
//			case SDL_SCANCODE_L:
//			{
//				m_MapVector.clear();
//				//Load Map
//				Load("map1.txt", "entity.sav");
//			} break;
//		}
//
//		// Handle Mouse input
//		switch (m_Input->GetMousePressed())
//		{
//			case 1:		// Left Mouse Clisk
//			{
//				// We need to judge where does it click
//				// Add codes for tiles and entities
//				int x = m_Input->GetX();
//				int y = m_Input->GetY();
//				
//				// Click on tileset
//				if (x <= TILE_MENU_X_TOTAL	&& y <= TILE_MENU_Y_TOTAL)
//				{
//					if (m_MapVector.size() > 0)
//					{
//						m_MapStack.push_back(m_MapVector);		// Save current state
//						cout << "Old state saved" << m_MapStack.size() << "\n";
//					}
//
//					/* Paint the tile
//			       Note that in reality tileset is 16*16
//				   But we will display every tile as 32*32
//				   So when we push, must divide GetNearestX
//				   and GetNearestY by 2 as they divide 32!
//				   But when draw (see draw() in cTile.cpp
//				   We must draw as 32*32 */
//
//					// Before push_back, delete duplicate
//					RemoveTile();
//					string id = GetTileIDByLocation();
//
//					m_MapVector.push_back(cTile(m_Graphics, m_Tilemap,
//								m_Painter.GetX()+m_XBias, m_Painter.GetY()+m_YBias,
//								GetNearestX(), GetNearestY(),
//								TILE_WIDTH, TILE_HEIGHT,1,
//								0,0,1,0,id));
//
//					// Need to delete this and re-write the savemap function
//					cout << "One tile pushed" << "\n";
//				}
//
//				//New click on tileset, need to create cLevel class
//				if (x <= TILE_MENU_X_TOTAL	&& y <= TILE_MENU_Y_TOTAL)
//				{
//					if (m_MapVector.size() > 0)
//					{
//						m_MapStack.push_back(m_MapVector);		// Save current state
//						cout << "Old state saved" << m_MapStack.size() << "\n";
//					}
//					/* Paint the tile
//			       Note that in reality tileset is 16*16
//				   But we will display every tile as 32*32
//				   So when we push, must divide GetNearestX
//				   and GetNearestY by 2 as they divide 32!
//				   But when draw (see draw() in cTile.cpp
//				   We must draw as 32*32 */
//
//					// Before push_back, delete duplicate
//					RemoveTile();
//					string id = GetTileIDByLocation();
//
//					m_MapVector.push_back(cTile(m_Graphics, m_Tilemap,
//								m_Painter.GetX()+m_XBias, m_Painter.GetY()+m_YBias,
//								GetNearestX(), GetNearestY(),
//								TILE_WIDTH, TILE_HEIGHT,1,
//								0,0,1,0,id));
//
//					// Need to delete this and re-write the savemap function
//					cout << "One tile pushed" << "\n";
//				}
//
//				// Click on entityset
//				if (x <= ENTITY_MENU_WIDTH * 
//					(m_GUI.GetEntityButton()).size()
//					&& y <= ENTITY_MENU_HEIGHT &&
//					y > ENTITY_MENU_HEIGHT - 32)
//				{
//					if (m_EntityVector.size() > 0)
//					{
//						m_EntityStack.push_back(m_EntityVector);		// Save current state
//						cout << "Old state saved" << m_MapStack.size() << "\n";
//					}
//
//					RemoveEntity();
//					string id = GetEntityIDByLocation();
//					cEntity temp = m_GUI.GetEntityByID(id,
//									m_Painter.GetX(), m_Painter.GetY());
//			//This is wrong, need to push back cEntity(...)
//			//The right way is to extract all information from temp
//			//and use push_back(cEntity(...))
//					m_EntityVector.push_back(cEntity(m_Graphics,
//					m_EntityPic, temp.GetX(), temp.GetY(),
//					temp.GetImageX(), temp.GetImageY(), 
//					temp.GetWidth(), temp.GetHeight(),
//					temp.GetID(), temp.GetHP(), temp.GetGold(),
//					temp.GetExp(), temp.GetInteractive(), 
//					0, temp.GetFrame()));
//
//					cout << m_EntityVector.size() << "\n";
//
//					cout << "One entity pushed" << "\n";
//				}
//
//				// If clicks on Save Button
//				if (x > GUIBoundaryX && x <= GUIBoundaryX + EDITOR_GUI_WIDTH)
//				{
//					if (y <= GUIBoundaryY + EDITOR_GUI_HEIGHT)	
//						m_MapData.SaveMap("map1.txt", m_MapVector);
//				}
//
//				if (x > GUIBoundaryX + EDITOR_GUI_WIDTH
//					&& x <= GUIBoundaryX + 2 * EDITOR_GUI_WIDTH)
//				{
//					if (y <= GUIBoundaryY + EDITOR_GUI_HEIGHT)	
//					{
//						Load("map1.txt", "entity.sav");	
//					}
//				}
//
//				if (x > GUIBoundaryX + 2 * EDITOR_GUI_WIDTH
//					&& x<= GUIBoundaryX + 3 * EDITOR_GUI_WIDTH)
//				{
//					if (y <= GUIBoundaryX + EDITOR_GUI_HEIGHT)
//					{
//						m_IsRunning = 0;	// Quit
//					}
//				}
//
//				if (x > GUIBoundaryX + 3 * EDITOR_GUI_WIDTH
//					&& x<= GUIBoundaryX + 4 * EDITOR_GUI_WIDTH)
//				{
//					if (m_XBias > EDITOR_BIAS_X_MIN)
//					{
//						m_XBias -= 32;	// Scroll to left
//						cout << m_XBias;
//					}
//				}
//
//				if (x > GUIBoundaryX + 4 * EDITOR_GUI_WIDTH
//					&& x<= GUIBoundaryX + 5 * EDITOR_GUI_WIDTH)
//				{
//					if (m_XBias < EDITOR_BIAS_X_MAX)
//					{
//						m_XBias += 32;	// Scroll to right
//						cout << "You changed xbias to " << m_XBias;
//					}
//				}
//			}break;
//			
//			case 2:
//			{
//				cout << "Middle Mouse Button Pressed" << "\n";
//				cout << m_Input->GetX() << " " 
//					<< m_Input->GetY() << "\n";
//				cout << GetNearestX() << " "
//						<< GetNearestY() << "\n";
//			}break;
//
//			case 3:
//			{
//				cout << "Right Mouse Button Pressed" << "\n";
//				cout << m_Input->GetX() << " " 
//					<< m_Input->GetY() << "\n";
//				cout << GetNearestX() << " "
//						<< GetNearestY() << "\n";
//			}break;
//		}
//	}
//
//	//// Handle keys being held down
//	//if ( m_Input->KeyHeld(SDL_SCANCODE_LEFT) && PlayerCanMoveLeft() )
//	//{
//	//	m_Player.MoveLeft();
//	//}
//	//if ( m_Input->KeyHeld(SDL_SCANCODE_RIGHT) && PlayerCanMoveRight() )
//	//{
//	//	m_Player.MoveRight();
//	//}
//	//if ( m_Input->KeyHeld(SDL_SCANCODE_SPACE) )
//	//{
//	//	cProjectile* proj = m_Player.Shoot();
//	//	if (proj != NULL)
//	//	{
//	//		m_PlayerProjectiles.push_back(proj);
//	//	}
//	//	proj = NULL;
//	//}
//}
//
//int cEditorState::GetNearestX()
//{
//	if (m_Input->GetX() > 0)
//	{
//		if (m_Input->GetX() % 32 == 0)	return m_Input->GetX();
//		return ((int) (m_Input->GetX() / 32)) * 32;
//	}
//	return 0;
//}
//
//int cEditorState::GetNearestY()
//{
//	if (m_Input->GetY() > 0)
//	{
//		if (m_Input->GetY() % 32 == 0)	return m_Input->GetY();
//		return ((int) (m_Input->GetY() / 32)) * 32;
//	}
//	return 0;
//}
//
//void cEditorState::DumpMap()
//{
//	vector<cTile>::iterator it;
//	for (it = m_MapVector.end(); it != m_MapVector.begin(); it --)
//	{
//		//cout << it->GetX() << " " << it->GetY() << "\n";
//	}
//}
//
//void cEditorState::BlinkTile()
//{
//	// Check where the cursor is
//	int x = m_Painter.GetX()+m_XBias;
//	int y = m_Painter.GetY()+m_YBias;
//	vector<cTile>::iterator it;
//
//	if (m_MapVector.size() == 0)
//	{
//		//cout << "No Map!" << "\n";
//		return;
//	}
//	// Check which tile is under the cursor rightnow
//	for (it = m_MapVector.begin(); it != m_MapVector.end(); it ++)
//	{
//		// If the cursor has left, unblink it
//		if ((*it).IsBlink())
//		{
//			if ((*it).GetX() != x || (*it).GetY() != y)
//			{
//				(*it).SetIsBlink(0);
//			}
//		}
//		if ((*it).GetX() == x && (*it).GetY() == y)
//		{
//			if ((*it).IsBlink())
//			{
//				return;
//			}
//			(*it).SetSpecial(1, EDITOR_BUTTON_BLINK, 
//								EDITOR_BUTTON_BLINK, 0);
//		}
//	}
//}
//
//void cEditorState::RemoveTile()
//{
//	vector<cTile>::iterator it;
//	if (m_MapVector.size() == 0)
//	{
//		cout << "No Map!" << "\n";
//		return;
//	}
//
//	for (it = m_MapVector.begin(); it != m_MapVector.end(); it ++)
//	{
//		if ((*it).GetX() == m_Painter.GetX()+m_XBias && 
//			(*it).GetY() == m_Painter.GetY()+m_YBias)
//		{
//			m_MapVector.erase(it);
//			break;
//		}
//	}
//}
//
//void cEditorState::RemoveEntity()
//{
//	vector<cEntity>::iterator it;
//	if (m_EntityVector.size() == 0)
//	{
//		cout << "No Entity!" << "\n";
//		return;
//	}
//
//	for (it = m_EntityVector.begin(); it != m_EntityVector.end(); it ++)
//	{
//		if ((*it).GetX() == m_Painter.GetX() && 
//			(*it).GetY() == m_Painter.GetY())
//		{
//			m_EntityVector.erase(it);
//			break;
//		}
//	}
//}
//
//string cEditorState::GetEntityIDByLocation()
//{
//	int x = m_Painter.GetX();
//	int y = m_Painter.GetY();
//	//Now we compare those values against 
//	//entities in m_GUIEntityVector
//	vector<cEntity>::iterator it;
//	for (it = (m_GUI.GetEntityButton()).begin();
//			it!= (m_GUI.GetEntityButton()).end(); it++)
//	{
//		if ((*it).GetX() == GetNearestX() && 
//			(*it).GetY() == GetNearestY())
//		{
//			DebugMessage("Found" + (*it).GetID());
//			return (*it).GetID();
//			break;
//		}
//	}
//	return "N/A";
//}
//
//string cEditorState::GetTileIDByLocation()
//{
//	int x = m_Painter.GetX();
//	int y = m_Painter.GetY();
//	//Now we compare those values against 
//	//entities in m_GUIEntityVector
//	vector<cStaticButton>::iterator it;
//	for (it = m_GUITileVector.begin(); it!= m_GUITileVector.end(); it++)
//	{
//		if ((*it).m_X == GetNearestX() && 
//			(*it).m_Y == GetNearestY())
//		{
//			return (*it).m_ID;
//			break;
//		}
//	}
//	return "N/A";
//}
//
//void cEditorState::Load(const char* mapfile, const char* entityfile)
//{
//	m_MapVector.clear();
//	//Load Map
//	m_MapData.LoadMap(mapfile, m_MapVector, m_Graphics, m_Tilemap);
//	m_EntityVector.clear();
//	m_EntityData.LoadEntityFromFile(entityfile, m_EntityVector,
//		m_Graphics, m_EntityPic);
//}
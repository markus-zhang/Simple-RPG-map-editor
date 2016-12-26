#include "cAI.h"
#include <random>
#include <stdlib.h>
#include <algorithm>

int cAIState::CanMove(std::vector<cTile> map, int x, int y)
{
	if (m_Player->GetX() == x && m_Player->GetY() == y)
	{
		DebugMessage("Cannot collide with player");
		return 0;
	}
	//DebugMessage("CanMove()");
	std::vector<cTile>::iterator it;
	for (it = map.begin(); it != map.end(); it ++)
	{
		if ((*it).GetX() == x && (*it).GetY() == y)
		{
			return (*it).GetAccess();
		}
	}
	DebugMessage("Cannot move");
	return 0;
}

void cIdleAIState::Init(std::vector<cTile> map, cEntityTest* owner, cEntityTest* player)
{
	if (map.size() <= 0 || !owner || !player)
	{
		DebugMessage("cIdleAIState: Error Init() NULL object");
		return;
	}
	m_Map = map;
	m_Owner = owner;
	m_Player = player;
}

void cIdleAIState::Think()
{
	Update(m_Owner, m_Map);
}

void cIdleAIState::Update(cEntityTest* owner, std::vector<cTile>& map)
{
	DebugMessage("I'm idle");
	// Generate random interger from 1-4
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(1, 5);
	auto direction = uni(rng);

	//std::cout << "Direction is " << direction << "\n";
	//direction = 5;	// Testing
	switch (direction)
	{
	case 1:	// North
	{
		int x_new = owner->GetX();
		int y_new = owner->GetY() - 32;
		if (CanMove(map, x_new, y_new) > 0)
		{
			owner->SetLocation(x_new, y_new);
		}
		break;
	}
	case 2:	// South
	{
		int x_new = owner->GetX();
		int y_new = owner->GetY() + 32;
		if (CanMove(map, x_new, y_new) > 0)
		{
			owner->SetLocation(x_new, y_new);
		}
		break;
	}	
	case 3:	// East
	{
		int x_new = owner->GetX() + 32;
		int y_new = owner->GetY();
		if (CanMove(map, x_new, y_new) > 0)
		{
			owner->SetLocation(x_new, y_new);
		}
		break;
	}	
	case 4:	// West
	{
		int x_new = owner->GetX() - 32;
		int y_new = owner->GetY();
		
		if (CanMove(map, x_new, y_new) > 0)
		{
			owner->SetLocation(x_new, y_new);
		}
		break;
	}
	case 5:	// Idle
	{
		break;
	}
	}
}

void cMoveAIState::Init(std::vector<cTile> map, cEntityTest* owner, cEntityTest* player)
{
	if (map.size() <= 0 || !owner || !player)
	{
		DebugMessage("cMoveAIState: Error Init() NULL object");
		return;
	}
	m_Map = map;
	m_Owner = owner;
	m_Player = player;
}

void cMoveAIState::Think()
{
	std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
	// Init() auto called by AIManager, calculate direction
	// And then call Update()
	// 1. Check if on same row/column
	if (m_Owner->GetX() == m_Player->GetX())
	{
		// Same column monster is north
		DebugMessage("Monster is due north of Player");
		if (m_Owner->GetY() < m_Player->GetY())
		{
			if (CanMove(m_Map, m_Owner->GetX(), m_Owner->GetY() + GAME_GRID))
			{
				m_Owner->SetLocation(m_Owner->GetX(), m_Owner->GetY() + GAME_GRID);
				return;
			}
			else
			{
				// Check the closet open node in South and move to it
				//             M
				// *****   ***************** *
				//             P
				// M will move to the opening to the left
				std::vector<cTile>::iterator it;
				int distance_x = 5120;
				for (it = m_Map.begin(); it != m_Map.end(); it++)
				{
					if ((*it).GetY() == m_Owner->GetY() + GAME_GRID)
					{
						if (abs((*it).GetX() - m_Owner->GetX()) <= distance_x)
						{
							distance_x = abs((*it).GetX() - m_Owner->GetX());
							// Set direction
							(*it).GetX() >= m_Owner->GetX() ? m_Direction = East : m_Direction = West;
							Update();
							return;
						}
					}
				}
			}
		}
		else
		{
			// Same column monster is south
			DebugMessage("Monster is due south of Player");
			if (CanMove(m_Map, m_Owner->GetX(), m_Owner->GetY() - 32))
			{
				m_Owner->SetLocation(m_Owner->GetX(), m_Owner->GetY() - 32);
				return;
			}
			else
			{
				// Check the closet open node in Nouth and move to it
				//             P
				// *****   ***************** *
				//             M
				// M will move to the opening to the left
				std::vector<cTile>::iterator it;
				int distance_x = 5120;
				for (it = m_Map.begin(); it != m_Map.end(); it++)
				{
					if ((*it).GetY() == m_Owner->GetY() - GAME_GRID)
					{
						if (abs((*it).GetX() - m_Owner->GetX()) <= distance_x)
						{
							distance_x = abs((*it).GetX() - m_Owner->GetX());
							// Set direction
							(*it).GetX() >= m_Owner->GetX() ? m_Direction = East : m_Direction = West;
							Update();
							return;
						}
					}
				}
			}
		}
	}
	
	if (m_Owner->GetY() == m_Player->GetY())
	{
		// Same row monster is west
		DebugMessage("Monster is due west of Player");
		if (m_Owner->GetX() < m_Player->GetX())
		{
			if (CanMove(m_Map, m_Owner->GetX() + GAME_GRID, m_Owner->GetY()))
			{
				m_Owner->SetLocation(m_Owner->GetX() + 32, m_Owner->GetY());
				return;
			}
			else
			{
				// Check the closet open node in East and move to it
				std::vector<cTile>::iterator it;
				int distance_y = 5120;
				for (it = m_Map.begin(); it != m_Map.end(); it++)
				{
					if ((*it).GetX() == m_Owner->GetX() + GAME_GRID)
					{
						if (abs((*it).GetY() - m_Owner->GetY()) <= distance_y)
						{
							distance_y = abs((*it).GetY() - m_Owner->GetY());
							// Set direction
							(*it).GetY() >= m_Owner->GetY() ? m_Direction = North : m_Direction = South;
							Update();
							return;
						}
					}
				}
			}
		}
		else
		{
			// Same column monster is east
			DebugMessage("Monster is due east of Player");
			if (CanMove(m_Map, m_Owner->GetX() - GAME_GRID, m_Owner->GetY()))
			{
				m_Owner->SetLocation(m_Owner->GetX() - GAME_GRID, m_Owner->GetY());
				return;
			}
			else
			{
				// Check the closet open node in West and move to it
				std::vector<cTile>::iterator it;
				int distance_y = 5120;
				for (it = m_Map.begin(); it != m_Map.end(); it++)
				{
					if ((*it).GetX() == m_Owner->GetX() - GAME_GRID)
					{
						if (abs((*it).GetY() - m_Owner->GetY()) <= distance_y)
						{
							distance_y = abs((*it).GetY() - m_Owner->GetY());
							// Set direction
							(*it).GetY() >= m_Owner->GetY() ? m_Direction = North : m_Direction = South;
							Update();
							return;
						}
					}
				}
			}
		}
	}
	// When they are not in the same row and column
	// Simply move closer
	DebugMessage("Not in the same row or column");
	MoveCloser();
	Update();
}

void cMoveAIState::MoveCloser()
{
	// So we already know they are not in same row/column
	int distance = abs(m_Owner->GetX() - m_Player->GetX()) +
		abs(m_Owner->GetY() - m_Player->GetY());
	// Loop through surrounding 4 tiles to find a better tile
	if (CanMove(m_Map, m_Owner->GetX(), m_Owner->GetY() - GAME_GRID))
	{
		// North, check if distance is shorter
		if (abs(m_Owner->GetX() - m_Player->GetX()) +
			abs(m_Owner->GetY() - GAME_GRID - m_Player->GetY()) < distance)
		{
			m_Direction = North;
		}
	}
	if (CanMove(m_Map, m_Owner->GetX(), m_Owner->GetY() + GAME_GRID))
	{
		// South, check if distance is shorter
		if (abs(m_Owner->GetX() - m_Player->GetX()) +
			abs(m_Owner->GetY() + GAME_GRID - m_Player->GetY()) < distance)
		{
			m_Direction = South;
		}
	}
	if (CanMove(m_Map, m_Owner->GetX() - GAME_GRID, m_Owner->GetY()))
	{
		// West, check if distance is shorter
		if (abs(m_Owner->GetX() - GAME_GRID - m_Player->GetX()) +
			abs(m_Owner->GetY() - m_Player->GetY()) < distance)
		{
			m_Direction = West;
		}
	}
	if (CanMove(m_Map, m_Owner->GetX() + GAME_GRID, m_Owner->GetY()))
	{
		// East, check if distance is shorter
		if (abs(m_Owner->GetX() + GAME_GRID - m_Player->GetX()) +
			abs(m_Owner->GetY() - m_Player->GetY()) < distance)
		{
			m_Direction = East;
		}
	}
}

void cMoveAIState::Update()
{
	DebugMessage("Updating Monster");
	switch (m_Direction)
	{
	case North:
	{
		m_Owner->SetLocation(m_Owner->GetX(), m_Owner->GetY() - GAME_GRID);
		std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
		break;
	}
	case South:
	{
		m_Owner->SetLocation(m_Owner->GetX(), m_Owner->GetY() + GAME_GRID);
		std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
		break;
	}
	case West:
	{
		m_Owner->SetLocation(m_Owner->GetX() - GAME_GRID, m_Owner->GetY());
		std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
		break;
	}
	case East:
	{
		m_Owner->SetLocation(m_Owner->GetX() + GAME_GRID, m_Owner->GetY());
		std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
		break;
	}
	default:
	{
		// Do not move
	}
	}
}


void cAttackAIState::Update(cEntityTest* owner, cEntityTest* target, cEffectFactory* effect_factory)
{
	if (target)
	{
		// Apply Damage effect on target
		effect_factory->CreateEffect("00_MODHP", 0,
			owner->GetAttributes().m_DmgDice * owner->GetAttributes().m_NumDmgDice,
			owner, target);
	}
}

cAIManager::cAIManager()
{
	m_IdleAI = new cIdleAIState;
	m_MoveAI = new cMoveAIState;
	//m_AttackAI = new cAttackAIState;
	m_CurrentAI = m_IdleAI;
}

cAIManager::~cAIManager()
{
	m_IdleAI = NULL;
	m_MoveAI = NULL;
	m_AttackAI = NULL;
	m_CurrentAI = NULL;
}

void cAIManager::Think(cEntityTest* owner, cEntityTest* player)
{
	DebugMessage("Thinking...");
	m_MoveAI->Init(m_Map, owner, player);
	m_IdleAI->Init(m_Map, owner, player);
	if (!owner || !player)
	{
		DebugMessage("Critical Error! No monster or player!");
	}
	//if (CanSeePlayer(owner, player))
	if (LOS(owner, player))
	{
		
		m_CurrentAI = m_MoveAI;
	}
	else
	{
		
		m_CurrentAI = m_IdleAI;
	}

	m_CurrentAI->Think();
}

bool cAIManager::LineInRectangle(int start_x, int start_y, int end_x, int end_y,
	int tile_x, int tile_y)
{
	// Check if all corners are on the same side of the line
	// Line equation: F(x y) = (y2-y1)*x + (x1-x2)*y + (x2*y1-x1*y2)
	/* If F(x y) = 0, (x y) is ON the line. 
	If F(x y) > 0, (x y) is "above" the line. 
	If F(x y) < 0, (x y) is "below" the line.*/

	int counter_zero, counter_greater, counter_smaller;
	counter_zero = counter_greater = counter_smaller = 0;

	int delta_y = end_y - start_y;
	int delta_x = start_x - end_x;
	int c = end_x * start_y - start_x * end_y;

	// Four Corners
	int value_ul = delta_y * tile_x + delta_x * tile_y + c;
	int value_ur = delta_y * (tile_x + GAME_GRID) + delta_x * tile_y + c;
	int value_lr = delta_y * (tile_x + GAME_GRID) + delta_x * (tile_y + GAME_GRID) + c;
	int value_ll = delta_y * tile_x + delta_x * (tile_y + GAME_GRID) + c;

	//  Print for Debug
	std::cout << "UL: " << value_ul << " UR: " << value_ur <<
		" LR: " << value_lr << " LL: " << value_ll << "\n";

	// calculate counters
	if (value_ul == 0)
	{
		counter_zero += 1;
	}
	else
	{
		if (value_ul > 0)
		{
			counter_greater += 1;
		}
		else
		{
			counter_smaller += 1;
		}
	}
	if (value_ur == 0)
	{
		counter_zero += 1;
	}
	else
	{
		if (value_ur > 0)
		{
			counter_greater += 1;
		}
		else
		{
			counter_smaller += 1;
		}
	}
	if (value_lr == 0)
	{
		counter_zero += 1;
	}
	else
	{
		if (value_lr > 0)
		{
			counter_greater += 1;
		}
		else
		{
			counter_smaller += 1;
		}
	}
	if (value_ll == 0)
	{
		counter_zero += 1;
	}
	else
	{
		if (value_ll > 0)
		{
			counter_greater += 1;
		}
		else
		{
			counter_smaller += 1;
		}
	}

	// If counter_zero == 1, and counter_greater or smaller == 3, pass
	if ((counter_zero == 1 && counter_greater == 3) ||
		(counter_zero == 1 && counter_smaller == 3))
	{
		DebugMessage("Only one intersection, pass");
		return false;
	}

	// If counter_greater or smaller == 4, pass
	if (counter_greater == 4 || counter_smaller == 4)
	{
		DebugMessage("No intersection, pass");
		return false;
	}

	// All others cannot pass
	DebugMessage("More than one intersection, blocked");
	return true;
}

bool cAIManager::LOS(cEntityTest* owner, cEntityTest* player)
{
	// If player is out of MONSTER_FOV, ignore
	int monster_x = owner->GetX();
	int monster_y = owner->GetY();
	int player_x = player->GetX();
	int player_y = player->GetY();

	if (abs(monster_x - player_x) > MONSTER_FOV ||
		abs(monster_y - player_y) > MONSTER_FOV)
	{
		DebugMessage("Player too far from me!");
		return false;
	}
	else
	{
		std::cout << abs(monster_y - player_y) << "\n";
		DebugMessage("Player in range");
	}

	// Now if player is in FOV we check the LOS from MIDDLEPOINT
	int monster_middle_x = monster_x + GAME_GRID / 2;
	int monster_middle_y = monster_y + GAME_GRID / 2;
	int player_middle_x = player_x + GAME_GRID / 2;
	int player_middle_y = player_y + GAME_GRID / 2;
	std::vector<cTile>::iterator it;
	int counter_blocker = 0;
	// Check for no blockers
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() == 0 &&
			(*it).GetX() >= std::min(monster_x, player_x) &&
			(*it).GetX() <= std::max(monster_x, player_x) &&
			(*it).GetY() >= std::min(monster_y, player_y) &&
			(*it).GetY() <= std::max(monster_y, player_y))
		{
			counter_blocker += 1;
		}
	}
	if (counter_blocker == 0)
	{
		DebugMessage("No blocker found!");
		return true;
	}
	// Upper Left corner of player occupied tile
	DebugMessage("Upper Left");
	int counter = 0;
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() != 0 ||
			(*it).GetX() < std::min(monster_x, player_x) ||
			(*it).GetX() > std::max(monster_x, player_x) ||
			(*it).GetY() < std::min(monster_y, player_y) ||
			(*it).GetY() > std::max(monster_y, player_y))
		{
			continue;
		}
		DebugMessage("One blocker");
		// Test for four vertices of player occupied tile
		// Once find one visible then check for other blocker tiles on this vertex
		if (LineInRectangle(monster_middle_x, monster_middle_y,
				player_x, player_y, (*it).GetX(), (*it).GetY()))
		{
			// Upper Left corner blocked by some blocker
			counter += 1;
			break;
		}
		else
		{
			continue;
		}
	}	
	if (counter == 0)
	{
		DebugMessage("Upper Left PASSED!");
		return true;
	}
	counter = 0;	// Reset
	DebugMessage("Upper Left Blocked!");
	DebugMessage("Lower Right");
	// Lower Right corner of player occupied tile
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() != 0 ||
			(*it).GetX() < std::min(monster_x, player_x) ||
			(*it).GetX() > std::max(monster_x, player_x) ||
			(*it).GetY() < std::min(monster_y, player_y) ||
			(*it).GetY() > std::max(monster_y, player_y))
		{
			continue;
		}
		DebugMessage("One blocker");
		// Test for four vertices of player occupied tile
		// Once find one visible then check for other blocker tiles on this vertex
		if (LineInRectangle(monster_middle_x, monster_middle_y,
			player_x + GAME_GRID, player_y + GAME_GRID, (*it).GetX(), (*it).GetY()))
		{
			// Lower Right corner blocked by some blocker
			counter += 1;
			break;
		}
		else
		{
			continue;
		}
		DebugMessage("Lower right PASSED!");
		return true;
	}
	if (counter == 0)
	{
		DebugMessage("Lower Right PASSED!");
		return true;
	}
	DebugMessage("Lower Right Blocked!");
	counter = 0;
	
	DebugMessage("Upper Right");
	// Upper Right corner of player occupied tile
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() != 0 ||
			(*it).GetX() < std::min(monster_x, player_x) ||
			(*it).GetX() > std::max(monster_x, player_x) ||
			(*it).GetY() < std::min(monster_y, player_y) ||
			(*it).GetY() > std::max(monster_y, player_y))
		{
			//DebugMessage("Block passed");
			continue;
		}
		DebugMessage("One blocker");
		// Test for four vertices of player occupied tile
		// Once find one visible then check for other blocker tiles on this vertex
		if (LineInRectangle(monster_middle_x, monster_middle_y,
			player_x + GAME_GRID, player_y, (*it).GetX(), (*it).GetY()))
		{
			// Upper Right corner blocked by some blocker
			counter += 1;
			break;
		}
		else
		{
			continue;
		}
		// Not blocked by each blocker
		DebugMessage("Upper Right PASSED!");
		return true;
	}
	if (counter == 0)
	{
		DebugMessage("Upper Right PASSED!");
		return true;
	}
	DebugMessage("Upper Right Blocked!");
	counter = 0;

	DebugMessage("Lower Left");
	// Lower Left corner of player occupied tile
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() != 0 ||
			(*it).GetX() < std::min(monster_x, player_x) ||
			(*it).GetX() > std::max(monster_x, player_x) ||
			(*it).GetY() < std::min(monster_y, player_y) ||
			(*it).GetY() > std::max(monster_y, player_y))
		{
			//DebugMessage("Block passed");
			continue;
		}
		DebugMessage("One blocker");
		// Test for four vertices of player occupied tile
		// Once find one visible then check for other blocker tiles on this vertex
		if (LineInRectangle(monster_middle_x, monster_middle_y,
			player_x, player_y + GAME_GRID, (*it).GetX(), (*it).GetY()))
		{
			// Lower Left corner blocked by some blocker
			DebugMessage("Lower Left blocked! Player not in my LOS");
			return false;
		}
		else
		{
			continue;
		}
	}
	// Not blocked by each blocker
	DebugMessage("Lower left PASSED! ALL PASSED!");
	return true;
}
#include "cBoard.h"
#include <iostream>

cGamePiece::cGamePiece()	{
	m_Row = m_Column = 0;
}

cGamePiece::~cGamePiece()	{
}

bool cBoard::PlaceQueen(int row, int column)	{
	RemoveDuplicate(row, column);
	if (CanPlaceQueen(row, column))	{
		cGamePiece temp;
		temp.m_Column = column;
		temp.m_Row = row;
		m_Game.push_back(temp);
		Draw();
		//SDL_Delay(2000);
		return true;
	}
	return false;
}

bool cBoard::CanPlaceQueen(int row, int column)	{
	std::cout << "Going to place " << "(" << row << " " << column << ")" << "\n";
	Draw();
	std::vector<cGamePiece>::iterator it;
	for (it = m_Game.begin(); it != m_Game.end(); it ++)	{
		if ((*it).m_Column == column || (*it).m_Row == row)
			return false;
		if (std::abs((*it).m_Column - column) == std::abs((*it).m_Row - row))
			return false;
	}
	std::cout << "(" << row << " " << column << ")" << " placed" << "\n";
	return true;
}

void cBoard::RemoveDuplicate(int row, int column)	{
	cout << "Check for " << row << " " << column << "\n";
	std::vector<cGamePiece>::iterator it;
	for (it = m_Game.begin(); it != m_Game.end(); it ++)	{
		if ((*it).m_Column == column)	{
			std::cout << (*it).m_Row << " " << (*it).m_Column << " is erased" << "\n";
			m_Game.erase(it);
			std::cout << "Erased!" << std::endl;
			Draw();
			return;
		}
	}
}

void cBoard::Draw()	{
	std::vector<cGamePiece>::iterator it;
	for (it = m_Game.begin(); it != m_Game.end(); it ++)	{
		std::cout << (*it).m_Row << " " << (*it).m_Column << std::endl;
	}
	std::cout << "**********************************" << std::endl;
}
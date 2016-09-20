#include "hanoi.h"

cHanoiManager::cHanoiManager()	{
	m_NumColumns = 3;
	cHanoiColumn temp;
	for (int i = 0; i < m_NumColumns; i++)	{
		if (i == 0)	{
			for (int j = 0; j < m_NumColumns; j++)	{
				temp.m_Pieces.push_back(3-j);
			}
			m_Game.push_back(temp);
		}
		else	{
			(temp.m_Pieces).push_back(0);
			m_Game.push_back(temp);
		}
		temp.m_Pieces.clear();
	}
}

void cHanoiManager::Dump()	{
	std::vector<cHanoiColumn>::iterator it;
	for (it = m_Game.begin(); it != m_Game.end(); it++)	{
		std::vector<int>::iterator it2;
		for (it2 = (*it).m_Pieces.begin(); it2 != (*it).m_Pieces.end(); it2++)	{
			std::cout << (*it2);
		}
		std::cout << "\n";
	}
}

int cHanoiManager::LocateValue(int piece)	{
	std::vector<cHanoiColumn>::iterator it;
	it = m_Game.begin();
	while (it != m_Game.end())	{
		if ((*it).m_Pieces.front() < piece)	{
			it ++;
		}
		else if ((*it).m_Pieces.front() == piece)	{
			return std::distance(m_Game.begin(), it);
		}
		else {
			std::vector<int>::iterator it2;
			for (it2 = (*it).m_Pieces.begin(); it2 != (*it).m_Pieces.end(); it2++)	{
				if ((*it2) == piece)
					return std::distance(m_Game.begin(), it);
			}
			it ++;
		}
	}
}

bool cHanoiManager::CanMove(int piece, int column)	{
	//First check if the piece is the last element
	int location;
	location = LocateValue(piece);
	if (m_Game[location].m_Pieces.back() != piece)
		return false;
	//If last non-zero element of target column is smaller than piece
	if (m_Game[column].m_Pieces.back() < piece && m_Game[column].m_Pieces.back() != 0)
		return false;
	return true;
}

void cHanoiManager::Move(int piece, int column)	{
	if (cHanoiManager::CanMove(piece, column))	{
		//First record the piece value
		int temp = piece;
		int source = cHanoiManager::LocateValue(piece);
		//Remove the piece, which is the last piece
		if (m_Game[cHanoiManager::LocateValue(piece)].m_Pieces.size() == 1)	{
			m_Game[cHanoiManager::LocateValue(piece)].m_Pieces.back() = 0;
		}
		else			
			m_Game[cHanoiManager::LocateValue(piece)].m_Pieces.pop_back();
		//Insert temp
		if (m_Game[column].m_Pieces.back() == 0) 
			m_Game[column].m_Pieces.pop_back();		//Remove zero
		m_Game[column].m_Pieces.push_back(temp);
	}
}

void cHanoiManager::Play()	{
	Move(1, 2);
	Move(2, 1);
	Move(1, 1);
	Dump();
}
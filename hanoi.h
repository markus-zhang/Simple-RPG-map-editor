#ifndef HANOI_
#define HANOI_

#include <vector>
#include <iostream>

struct cHanoiColumn	{
	std::vector<int> m_Pieces;
};

class cHanoiManager	{
private:
	std::vector<cHanoiColumn> m_Game;
	int m_NumColumns;
public:
	cHanoiManager();
	~cHanoiManager();

	int LocateValue(int piece);			// Return the position of a piece
	bool CanMove(int piece, int column);// Return if piece can move to column
	void Move(int piece, int column);	// Move piece to column

	void Dump();
	void Play();
};

#endif
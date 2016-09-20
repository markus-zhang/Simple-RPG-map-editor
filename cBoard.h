#ifndef CBOARD_H_
#define CBOARD_H_

#include <vector>
#include <cmath> 
#include "cGraphics.h"

struct cGamePiece	{
	int m_Row;
	int m_Column;

	cGamePiece();
	~cGamePiece();
};

class cBoard	{
private:
	std::vector<cGamePiece> m_Game;
public:
	bool PlaceQueen(int row, int column);
	void RemoveDuplicate(int row, int column);
	bool CanPlaceQueen(int row, int column);
	void Draw();
};
#endif
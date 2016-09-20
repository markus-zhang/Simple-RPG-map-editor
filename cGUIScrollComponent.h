#ifndef CGUISCROLLCOMPONENT_
#define CGUISCROLLCOMPONENT_

#include "cStaticButton.h"
#include <vector>

class cGUIScrollComponent
{
private:
	std::vector<cStaticButton> m_GeneralButton;
	cStaticButton m_ScrollLeft;
	cStaticButton m_ScrollRight;
	int m_GeneralBoundaryX;		// To check if a GUI button
	int m_GeneralBoundaryY;		// has been clicked on
	int m_MaximumDisplay;	// How many buttons
	int m_XBias;				// For scrolling
public:
	cGUIScrollComponent();
	~cGUIScrollComponent();

	std::vector<cStaticButton>& GetGeneralButton();

	int GetBoundaryX()	{ return m_GeneralBoundaryX; }
	int GetBoundaryY()	{ return m_GeneralBoundaryY; }

	bool CanScrollLeft();	// If can't scroll, DrawModulate()
	bool CanScrollRight();

	void Draw();

	//"Tile" for clicking on tiles, "Entity" for clicking on entities
	std::string OnClick(int mouseX, int mouseY);

	void SetGeneralBoundary(int x, int y)	{ 
		m_GeneralBoundaryX = x;
		m_GeneralBoundaryY = y;
	}
};

#endif
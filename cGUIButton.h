// Header file for buttons on GUI
#include "cGraphics.h"
#include "Defines.h"

class cGUIButton
{
public:
	cGUIButton(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y,
				int img_x1, int img_y1, int img_x2,
				int img_y2, int width, int height);
	cGUIButton() {}
	
	void Draw();

	//These buttons blink for 30 frames when clicked
	void onClickTemp();	
	//These buttons change for ever when clicked
	void onClickPerm();
	void Reset();

//private:
	//Graphics
	cGraphics* m_Graphics;
	SDL_Texture* m_Bitmap;

	//Animation
	int m_Frame;
	int m_AnimationTime;		// For example 50ms
	SDL_Rect m_Animation[2];	// Two frames for the button

	//Screen location 
	int m_X;
	int m_Y;

	//Clip location
	int m_ImageX;
	int m_ImageY;

	//Dimensions
	int m_Width;
	int m_Height;
};
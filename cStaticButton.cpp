#include "cStaticButton.h"
#include <iostream>

cStaticButton::cStaticButton(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y, int img_x, int img_y, int width, int height)
{
	m_Graphics = graphics;
	m_Bitmap = bitmap;

	m_ID = "Blah";

	m_X = x;
	m_Y = y;

	m_ImageX = img_x;
	m_ImageY = img_y;

	m_Width = width;
	m_Height = height;
}

cStaticButton::cStaticButton(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y, int img_x, int img_y, int width, int height,
				string id)
{
	m_Graphics = graphics;
	m_Bitmap = bitmap;

	m_ID = id;

	m_X = x;
	m_Y = y;

	m_ImageX = img_x;
	m_ImageY = img_y;

	m_Width = width;
	m_Height = height;
}

void cStaticButton::Draw()
{
	m_Graphics->RenderTexture(m_Bitmap, m_ImageX, 
						m_ImageY, m_X, m_Y, m_Width, m_Height);
}
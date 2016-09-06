#include "cGUIButton.h"
#include <iostream>

cGUIButton::cGUIButton(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y,
				int img_x1, int img_y1, int img_x2,
				int img_y2, int width, int height)
{
	m_Graphics = graphics;
	m_Bitmap = bitmap;

	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;

	m_Animation[0].x = img_x1;
	m_Animation[0].y = img_y1;
	m_Animation[0].w = width;
	m_Animation[0].h = height;

	m_Animation[1].x = img_x2;
	m_Animation[1].y = img_y2;
	m_Animation[1].w = width;
	m_Animation[1].h = height;

	m_Frame = 0;
	m_AnimationTime = 0;
}

void cGUIButton::Draw()
{
	if (m_AnimationTime > 0 && m_AnimationTime <= EDITOR_BUTTON_BLINK)
	{
		m_Frame = 1;
		m_AnimationTime += 1;	// Increases 1 every frame
	}
	if (m_AnimationTime > EDITOR_BUTTON_BLINK)
	{
		Reset();				// After some frames, back to original
	}
	m_Graphics->RenderTexture(m_Bitmap, m_Animation[m_Frame].x, 
		m_Animation[m_Frame].y, m_X, m_Y, m_Width, m_Height);
}

void cGUIButton::onClickTemp()
{
	m_AnimationTime += 1;	// Triggers the conditions in Draw()
}

void cGUIButton::onClickPerm()
{
	m_Frame = 1 - m_Frame;	// The other frame
}

void cGUIButton::Reset()
{
	m_AnimationTime = 0;
	m_Frame = 0;
}
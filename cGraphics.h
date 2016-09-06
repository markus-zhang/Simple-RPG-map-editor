//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
// - NOTE this class assumes that you will create your own SDL_Surface variables for
// each image you wish to display. Call LoadImage() and CloseImage() to create and 
// destroy your SDL_Surface variables.
// - NOTE call DrawImage() to draw an SDL_Surface. Call Show() to display your scene.
//////////////////////////////////////////////////////////////////////////////////

#pragma once

//SDL 2.0 code for libraries
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_TTF.lib")

#include <string>    
#include "SDL.h"     
#include "SDL_TTF.h" 
#include "SDL_image.h"

using namespace std;

class cGraphics
{
public:
	cGraphics(int wndWidth, int wndHeight, string wndCaption);
	~cGraphics();
	
	//SDL 2.0 code to load a texture
	//Note that text and image share the same m_Texture
	//So either this object is for a text, or it's for an image
	//YOU CANNOT MIX BOTH!
	SDL_Texture* LoadTexture(string filename, int r, int g, int b);

	//SDL 2.0 code to render a texture at (x, y)
	void RenderTexture(SDL_Texture* texture, int srcX, int srcY, int desX, int desY,
						int width, int height);

	void RenderTileSet(SDL_Texture* texture, int srcX, int srcY, int desX, int desY,
						int srcWidth, int srcHeight, 
						int desWidth, int desHeight);

	void RenderTest();

	//SDL 2.0 code to clear screen
	void ClearScreen();

	//SDL 2.0 code to update screen for image and text
	//Step 1: LoadTexture or LoadText
	//Step 2: RenderTexture
	//Step 3: Show()
	void Show();

	void CloseImage(SDL_Texture* texture);

	//SDL 2.0 code to load text
	void LoadText(string text, int size, int r, int g, int b);

	//SDL 2.0 code to render text in ONE function
	void RenderText(string text, int size, int r, int g, int b,
					int srcX, int srcY);

private:
	//SDL 2.0 code
	SDL_Window* m_Window;			//1st, load image to this
	SDL_Texture* m_Texture;	//2nd, make texture from surface
	SDL_Renderer* m_Renderer;	//3rd, renderer the texture on screen
};

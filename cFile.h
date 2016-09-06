#ifndef CFILE_
#define CFILE_
// File load/save class

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "cTile.h"
#include "cStaticButton.h"
#include "cEntity.h"
#include "DebugTool.h"

class cFile
{
friend class cEditorState;
private:
	//cTile m_Tile;		// Information holder
	//vector<cTileFile>	m_MapFile;
	vector<cStaticButton>  m_GUIButtonVector;
	vector<cEntity>	m_Entity;
	vector<string> m_EntityString;

public:
	cFile();
	~cFile();
	
	cEntity GetEntityByID(string ID, int x, int y);

	// CheckFile checks if:
	// 1. File does not exist;
	// 2. File is not of proper arrangement;
	// 3. File is copy-protected.
	// Filetype = GUI ini / Map file
	bool CheckFile(const char* filename, int filetype);

	// "guisetting" gives the information of
	// 1. The name of GUI components (e.g. Save Button)
	// 2. Followed by its position on screen
	// 3. Followed by the position on tileset (clip) of first frame
	// 4. Followed by width and height
	// 5. Followed by the position on tileset of second frame
	bool LoadGUI(const char* guisetting);
	bool LoadEntityGUI(const char* entityfile);
	bool SaveEntity(const char* filename, const vector<cEntity>& entityvector);
	bool LoadEntityFromFile(const char* filename,
			vector<cEntity>& entityvector,
			cGraphics* graph, SDL_Texture* bitmap);

	//bool LoadMap(const char* filename);
	bool LoadMap(const char* filename, vector<cTile>& mapvector, 
				cGraphics* graph, SDL_Texture* bitmap);
	//bool SaveMapOld(const char* filename);

	bool SaveMap(const char* filename, const vector<cTile>& mapvector);

	void Remove(int x, int y, vector<cTile>& mapvector);
};
#endif
#include "cEditorAction.h"

bool cSaveMapAction::Execute(const char* filename,
	const std::vector<cTile>& mapvector,
	std::string mapid, int playerx, int playery)
{
	/*	Saves the map to the file designated
	*****************
	Sample structure of map.txt:
	0		#ClipX
	0		#ClipY
	128		#ScreenX
	32		#ScreenY
	64		#Width
	32		#Height
	1		#Accessible
	******************
	Maybe we can also use TinyXML
	*/
	std::cout << mapvector.size() << "\n";
	std::vector<cTile>::iterator it;
	std::ofstream map_file;
	std::string id = mapid;

	// Clear the txt before writing
	map_file.open(filename, std::fstream::out | std::fstream::trunc);

	if (!map_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}
	//Now save the data line by line
	//Save map id first
	map_file << "<MapID>" << id << "</MapID>" << "\n";
	//Save player start next
	map_file << "<PlayerX>" << std::to_string(playerx) << "</PlayerX>" << "\n";
	map_file << "<PlayerY>" << std::to_string(playery) << "</PlayerY>" << "\n";
	for (auto it = mapvector.begin(); it != mapvector.end(); it++)
	{
		std::string id = (*it).GetID();
		char access = id.at(0);	// First char of ID
		map_file << (*it).GetID() << "\n";
		map_file << (*it).GetX() << "\n";
		map_file << (*it).GetY() << "\n";
		map_file << (*it).GetImageX() << "\n";
		map_file << (*it).GetImageY() << "\n";
		map_file << (*it).GetWidth() << "\n";
		map_file << (*it).GetHeight() << "\n";
		//map_file << (*it).GetIsAccessible() << "\n";
		std::cout << (*it).GetX() << " " << (*it).GetY() << "\n";
		map_file << access << "\n";
	}
	map_file.close();
	return true;

}
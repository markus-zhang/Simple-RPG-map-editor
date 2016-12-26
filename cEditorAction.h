#ifndef CEDITORACTION_H_
#define CEDITORACTION_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "cTile.h"

class cFile;


class cAction
{
public:
	virtual void Execute();
};

class cTestAction : public cAction
{
public:
	virtual void Execute(int x, int y) 
	{
		std::cout << "Sum is " << x + y << "\n";
	}
};


class cSaveMapAction : public cAction
{
	virtual bool Execute(const char* filename,
		const std::vector<cTile>& mapvector,
		std::string mapid, int playerx, int playery);
};

#endif

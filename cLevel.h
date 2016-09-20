#ifndef CLEVEL_
#define CLEVEL_

#include "cTile.h"
#include "cEntity.h"

class cLevel
{
private:
	std::string m_ID;
	std::vector<cEntity> m_Entity;
	std::vector<cTile>   m_Map;
	std::vector < std::vector<cTile> > m_MapStack;		// For Undo
	std::vector < std::vector<cEntity> > m_EntityStack;	// For Undo
public:
	cLevel();
	~cLevel();

	std::vector<cTile>& GetMap(){ return m_Map; }
	std::vector<cEntity>& GetEntity() { return m_Entity; }
	std::vector< std::vector<cTile> >& GetMapStack() { return m_MapStack; }
	std::vector< std::vector<cEntity> >& GetEntityStack() { return m_EntityStack; }

	int GetTileAccess(int x, int y);
	void OnEnter();
	void OnExit();

	void RemoveTile(int x, int y, int xbias, int ybias);
	void RemoveEntity(int x, int y, int xbias, int ybias);
	void SaveMapState();
	void SaveEntityState();
	void Undo();

	void PushTile();
};

#endif
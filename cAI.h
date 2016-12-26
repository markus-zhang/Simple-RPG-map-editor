// The AI interface; Different AIs; AI Manager

#ifndef CAI_H_
#define CAT_H_

#include "cEntityFactory.h"
#include "cTile.h"
#include "cEffect.h"
#include "Enums.h"

class cAIState
{
public:
	virtual void Think() = 0;
	int CanMove(std::vector<cTile> map, int x, int y);
protected:
	cEntityTest* m_Player;
};

// Idle State, monsters move around randomly
class cIdleAIState : public cAIState
{
public:
	void Init(std::vector<cTile> map, cEntityTest* owner, cEntityTest* player);
	void Think();
	void Update(cEntityTest* owner, std::vector<cTile>& map);
private:
	std::vector<cTile> m_Map;
	cEntityTest* m_Owner;
	
};

// Move State
//enum Direction	{North, South, West, East};
class cMoveAIState : public cAIState
{
public:
	void Init(std::vector<cTile> map, cEntityTest* owner, cEntityTest* player);
	void Think();
	void Update();
	void MoveCloser();
private:
	std::vector<cTile> m_Map;
	cEntityTest* m_Owner;
	//cEntityTest* m_Player;
	int m_Direction;
};

// Attack State
class cAttackAIState : public cAIState
{
public:
	void Update(cEntityTest* owner, cEntityTest* target, cEffectFactory* effect_factory);
};

class cAIManager
{
public:
	cAIManager();
	~cAIManager();

	void Think(cEntityTest* owner, cEntityTest* player);
	int CloseEnough(cEntityTest* owner, cEntityTest* player);
	bool CanMove(cEntityTest* owner, std::vector<cTile> map) const;
	//bool CanSeePlayer(cEntityTest* owner, cEntityTest* player);
	bool LOS(cEntityTest* owner, cEntityTest* player);
	void SetCurrentAI(cEntityTest* owner);
	void SetMap(const std::vector<cTile>& map)
	{
		m_Map = map;
	}
	//int CountVertices(int start_x, int start_y, int end_x, int end_y,
		//int tile_x, int tile_y, bool larger);

	bool LineInRectangle(int start_x, int start_y,
		int end_x, int end_y, int tile_x, int tile_y);

private:
	std::vector<cTile> m_Map;

	cIdleAIState* m_IdleAI;
	cMoveAIState* m_MoveAI;
	cAttackAIState* m_AttackAI;

	cAIState* m_CurrentAI;
};

#endif

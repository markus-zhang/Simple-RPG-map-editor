#ifndef CENEMY_H_
#define CENEMY_H_

#include "cEntity.h"

class cEnemy : public cEntity
{
public:
	//LoadAtt() should be in some cEnemyManager
	void LoadAtt(std::string id);	// Called when loaded, to load str/etc.

	int GetStr()		{ return m_ATT_STR; }
	int GetDex()		{ return m_ATT_DEX; }
	int GetCon()		{ return m_ATT_CON; }
	int GetDmg()		{ return m_COM_SPEED * 
							(m_COM_Basedmg + m_COM_Weapondmg); }

	//onSpawn() and onDeath() are just for test, real ones
	//are in m_EntityManager
	void onSpawn();		
	void onDeath();
	//just check if there is obstacle in between
	bool seePlayer(int playerX, int playerY, bool playerInv);
	void move();

private:
	// Attributes
	int m_ATT_STR;
	int m_ATT_DEX;
	int m_ATT_CON;
	
	// Combat
	int m_COM_Basedmg;
	int m_COM_Weapondmg;
	int m_COM_Speed;		// dmg = speed * (base+weapon dmg)
	int m_COM_FOV;			// let's give them a 5 or 6
};

#endif
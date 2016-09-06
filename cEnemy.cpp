#include "cEnemy.h"

void cEnemy::LoadAtt(std::string id)
{
	// Find a match in the database
}

void cEnemy::onSpawn()
{
	DebugMessage(m_ID + " is spawned!");	
}

void cEnemy::onDeath()
{
	//In the update() of m_EntityManager, all entities get updated
	//per game loop. When an entity has an HP <= 0, it will be removed.
	//Before we remove this entity, we will run the onDeath() FROM
	//m_EntityManager INSTEAD OF FROM HERE. In that onDeath we will
	//call GetExp() and GetGold() of this entity and then call
	//SetExp() and SetGold() of the player entity. Because the entity
	//manager has access to all the entities (including the player
	//entity, this would be a much better idea
	DebugMessage("Reward experience and gold to the player!");
}
#ifndef CEFFECT_H_
#define CEFFECT_H_

#include <string>
#include <vector>
#include "cTimer.h"
#include "cEntityTest.h"

class cEffect
{
private:
	// 00_SUBHP, 00_ADDHP, etc. 00_ means permenant effect
	// 01_POISON, 01_SLEEP, etc. 01_ means timed effect
	std::string m_ID;
	cEntityTest* m_Owner;
	cEntityTest* m_Target;
	int m_Life;
	int m_Value;
	cTimer m_LifeTimer;
public:
	cEffect(std::string id);
	std::string GetID() { return m_ID; }
	void SetOwner(cEntityTest* owner)
	{
		if (owner)
		{
			m_Owner = owner;
		}
	}

	void SetTarget(cEntityTest* target)
	{
		if (target)
		{
			m_Target = target;
		}
	}

	void SetLife(int life)
	{
		m_Life = life;
	}

	void SetValue(int value)
	{
		m_Value = value;
	}

	void Update();
	bool Expire()
	{
		if (m_Life <= 0)
		{
			return true;
		}
		return false;
	}
	void ApplyEffect();
};


class cEffectFactory
{
private:
	std::vector<cEffect*> m_EffectFactory;
	std::vector<cEffect*> m_EffectCreated;
public:
	std::vector<cEffect*>& GetFactory()
	{
		return m_EffectFactory;
	}
	void Update();
	void CreateEffect(std::string id, int life, int value, cEntityTest* owner, cEntityTest* target);
	//void RegisterEffect(cEntityTest* owner, cEntityTest* target);
	void ApplyEffect();
};

#endif

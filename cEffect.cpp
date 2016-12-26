#include "cEffect.h"

cEffect::cEffect(std::string id)
{
	m_ID = id;
	m_LifeTimer.Reset();
}

void cEffect::Update()
{
	m_Life -= m_LifeTimer.GetMilliseconds();
	m_LifeTimer.Reset();
}

void cEffect::ApplyEffect()
{
	if (!m_Target)
	{
		DebugMessage("Effect Target cannot be found!");
		return;
	}
	if (m_ID == "00_MODHP")
	{
		if (m_Target)
		{
			if ((m_Target->GetAttributes()).m_HP > 0)
			{
				m_Target->GetAttributes().m_HP += m_Value;
			}
			else
			{
				DebugMessage("The target is already dead!");
			}
		}
	}

	if (m_ID == "01_POISON")
	{

	}
}

void cEffectFactory::Update()
{
	ApplyEffect();
	std::vector<cEffect*>::iterator it;
	for (it = m_EffectCreated.begin(); it != m_EffectCreated.end(); it++)
	{
		if ((*it)->Expire())
		{
			m_EffectCreated.erase(it);
			if (m_EffectCreated.size() <= 0)
			{
				return;
			}
		}
		(*it)->Update();
	}
}

void cEffectFactory::CreateEffect(std::string id, int life, int value, cEntityTest* owner, cEntityTest* target)
{
	// First check if the effect has been registered
	std::vector<cEffect*>::iterator it;
	for (it = m_EffectFactory.begin(); it != m_EffectFactory.end(); it++)
	{
		if ((*it)->GetID() == id)
		{
			cEffect* new_effect = new cEffect(id);
			new_effect->SetLife(life);
			new_effect->SetValue(value);
			if (owner && target)
			{
				new_effect->SetOwner(owner);
				new_effect->SetTarget(target);
			}
			if (new_effect)
			{
				m_EffectCreated.push_back(new_effect);
			}
		}
	}
	DebugMessage("Cannot create effect, something goes wrong!");
}

void cEffectFactory::ApplyEffect()
{
	std::vector<cEffect*>::iterator it;
	for (it = m_EffectCreated.begin(); it != m_EffectCreated.end(); it++)
	{
		(*it)->ApplyEffect();
	}
}
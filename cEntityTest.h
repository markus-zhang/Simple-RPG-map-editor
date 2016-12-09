#ifndef CENTITYTEST_H_
#define CENTITYTEST_H_

#include <unordered_map>
#include <vector>
#include "cGraphics.h"
#include "cAnimation.h"

struct cAttributes
{
	int m_HP;
	int m_AC;
	int m_DmgDice;
	int m_NumDmgDice;
	int m_Speed;
	int m_Exp;
	int m_Gold;
};
class cEntityTest
{
public:
	cEntityTest();
	~cEntityTest();

	int GetX() { return m_X; }
	int GetY() { return m_Y; }

	void SetAttributes(cAttributes attributes)
	{
		m_Attributes = attributes;
	}
	void SetLocation(int x, int y)
	{
		m_X = x;
		m_Y = y;
	}
	void RegisterAnimation(cAnimation ani)
	{
		m_Animation.push_back(ani);
	}
	void Update();
	void SetAnimation(std::string id);
	void PlayAnimation(std::string id);
	void PlayAnimationBiased(std::string id,
		int xbias, int ybias);
	void PlayAnimation();
	void Init();
	void Dump();
	void SetGraphics(cGraphics* graphics, SDL_Texture* texture)
	{
		std::vector<cAnimation>::iterator it;
		for (it = m_Animation.begin(); it != m_Animation.end(); it++)
		{
			(*it).SetGraphics(graphics, texture);
		}
	}
private:
	cAttributes m_Attributes;
	int m_X, m_Y;

	//Animation
	std::vector<cAnimation> m_Animation;
	std::string m_CurrentAnimation;
	std::unordered_map<std::string, cAnimation> m_AnimationMap;
};

#endif


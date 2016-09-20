#include "cGUIScrollComponent.h"

cGUIScrollComponent::cGUIScrollComponent(){
	m_GeneralBoundaryX = m_GeneralBoundaryY = 0;
	m_MaximumDisplay = 10;
	m_XBias = 0;
}
cGUIScrollComponent::~cGUIScrollComponent(){}

std::vector<cStaticButton>& cGUIScrollComponent::GetGeneralButton()	{
	return m_GeneralButton;
}

bool cGUIScrollComponent::CanScrollLeft()	{
	if (m_XBias == 0) 
		return false;
	return true;
}

bool cGUIScrollComponent::CanScrollRight()	{
	if (m_GeneralButton.size() <= m_XBias + m_MaximumDisplay) 
		return false;
	return true;
}

void cGUIScrollComponent::Draw()	{
	for (size_t i=0; i<m_GeneralButton.size(); i++)
	{
		m_GeneralButton[i].Draw();
	}

	if (CanScrollLeft())	{
		m_ScrollLeft.Draw();
	}
	else	{
		m_ScrollLeft.DrawModulate(211, 211, 211, 0);
	}

	if (CanScrollRight())	{
		m_ScrollRight.Draw();
	}
	else	{
		m_ScrollRight.DrawModulate(211, 211, 211, 0);
	}
}

std::string cGUIScrollComponent::OnClick(int mouseX, int mouseY)	{
	//First we check m_GeneralButton
	vector<cStaticButton>::iterator it;
	for (it = m_GeneralButton.begin(); it != m_GeneralButton.end(); it++)	{
		if ((*it).GetX() == mouseX && (*it).GetY() == mouseY)	{
			if ((*it).GetID().at(0) == '0') return "Tile";
			if ((*it).GetID().at(0) == '1') return "Entity";
			if ((*it).GetID().at(0) == '2') return "General";
		}
	}
}
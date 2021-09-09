#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned level)
{
	m_Level = level;
	m_Exp = 0;
	m_ExpNext = static_cast<unsigned>((50 / 3) * (pow(m_Level, 3) - 6 * pow(m_Level, 2) + (m_Level * 17) - 12));
	m_AttributePoints = 2;

	m_Vitality = 1;
	m_Strength = 1;
	m_Dexterity = 1;
	m_Agility = 1;
	m_Intelligence = 1;

	updateLevel();
	updateStats(true);
}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::updateStats(const bool reset)
{
	m_HpMax = m_Vitality * 5 + m_Vitality + m_Strength / 2 + m_Intelligence / 5;
	m_DamageMin = m_Strength * 2 + m_Strength / 4 + m_Intelligence / 5;
	m_DamageMax = m_Strength * 2 + m_Strength / 2 + m_Intelligence / 5;
	m_Accuracy = m_Dexterity * 5 + m_Dexterity / 2 + m_Intelligence / 5;
	m_Defence = m_Agility * 2 + m_Agility / 4 + m_Intelligence / 5;
	m_Luck = m_Intelligence * 2 + m_Intelligence / 5;

	if (reset)
	{
		m_Hp = m_HpMax;
	}
}

void AttributeComponent::updateLevel()
{
	while (m_Exp >= m_ExpNext)
	{
		++m_Level;
		m_Exp -= m_ExpNext;
		m_ExpNext = static_cast<unsigned>((50 / 3) * (pow(m_Level, 3) - 6 * pow(m_Level, 2) + (m_Level * 17) - 12));
		++m_AttributePoints;
	}
}

void AttributeComponent::gainExp(const unsigned exp)
{
	m_Exp += exp;

	updateLevel();
}

void AttributeComponent::update()
{
	updateLevel();

}

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;
	ss << "Level: " << m_Level << "\n"
		<< "Exp: " << m_Exp << "\n"
		<< "Exp Next: " << m_ExpNext << "\n"
		<< "Attp: " << m_AttributePoints << "\n";

	return ss.str();
}

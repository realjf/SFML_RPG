#pragma once


class AttributeComponent
{
public:
	AttributeComponent(unsigned level);
	~AttributeComponent();

	void updateStats(const bool reset);
	void updateLevel();
	void gainExp(const unsigned exp);
	void update();
	std::string debugPrint() const;

public:
	// leveling
	unsigned m_Level;
	unsigned m_Exp;
	unsigned m_ExpNext;
	unsigned m_AttributePoints;

	// attributes
	int m_Vitality;
	int m_Strength;
	int m_Dexterity;
	int m_Agility;
	int m_Intelligence;

	// stats
	int m_Hp;
	int m_HpMax;
	int m_DamageMin;
	int m_DamageMax;
	int m_Accuracy;
	int m_Defence;
	int m_Luck;

};


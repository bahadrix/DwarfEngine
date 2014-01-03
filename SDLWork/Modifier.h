#pragma once
class Dwarf;
class Modifier {
public:
	Modifier(void);
	~Modifier(void);
	virtual void preRender(void);
protected:
	Dwarf *target;

	friend class Dwarf;
};


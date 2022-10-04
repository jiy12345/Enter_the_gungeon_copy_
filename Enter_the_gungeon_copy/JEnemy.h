#pragma once
#include "JBaseCharacter.h"
#include "gr_black_revolver.h"

class JEnemy : public JBaseCharacter
{
public:
	bool init() override;
	bool frame() override;
};


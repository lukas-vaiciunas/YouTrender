#pragma once

#include "Visual.h"

class RandColorVisual : public Visual
{
private:
	void updateOutput();
public:
	RandColorVisual(unsigned int width, unsigned int height);
};
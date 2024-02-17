#pragma once
#include "movieobject.h"

class User : public MovieObject {
public:
	void draw() override;
	void update() override;
	void init() override;
};
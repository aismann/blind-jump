//
//  inputController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef inputController_hpp
#define inputController_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class InputController {
private:
	bool left, right, up, down, x, z, c;
	
public:
	InputController();
	bool leftPressed() const;
	bool rightPressed() const;
	bool upPressed() const;
	bool downPressed() const;
	bool xPressed() const;
	bool zPressed() const;
	bool cPressed() const;
	void setLeft(const bool);
	void setRight(const bool);
	void setUp(const bool);
	void setDown(const bool);
	void setX(const bool);
	void setZ(const bool);
	void setC(const bool);
};

#endif /* inputController_hpp */
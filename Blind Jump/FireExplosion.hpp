//
//  FireExplosion.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef FireExplosion_hpp
#define FireExplosion_hpp

#include "SFML/Graphics.hpp"

class FireExplosion {
private:
    sf::Sprite sprites[9];
    sf::Sprite glow;
    float xInit, yInit, xPos, yPos;
    bool killFlag;
    char frameIndex, frameRate;
    
public:
    FireExplosion(sf::Sprite*, sf::Sprite, float, float);
    void update(float, float);
    sf::Sprite getSprite();
    bool getKillFlag();
    float getYpos();
    sf::Sprite* getGlow();
};

#endif /* FireExplosion_hpp */
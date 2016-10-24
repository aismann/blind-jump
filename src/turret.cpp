//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include <cmath>
#include "angleFunction.hpp"
#include "player.hpp"
#include "turret.hpp"

Turret::Turret(const sf::Texture & gameObjects, float _xPos, float _yPos) :
    state(State::closed),
    xPos(_xPos),
    yPos(_yPos),
    frameIndex(0),
    timer(0),
    hp(6),
    killFlag(0),
    colorTimer(0),
    isColored(0),
    colorAmount(0)
{
    turretSheet.setTexture(gameObjects);
    shadowSheet.setTexture(gameObjects);
    hitBox.setPosition(xPos, yPos);
    turretSheet.setPosition(xPos, yPos);
    shadowSheet.setPosition(xPos, yPos + 18);
    hitBox.setPosition(xPos, yPos);
}

const framework::Sprite & Turret::getSprite() {
    return turretSheet[frameIndex];
}

void Turret::update(const sf::Time & elapsedTime, const Player * player, EffectGroup & effects) {
    if (isColored) {
        colorTimer += elapsedTime.asMilliseconds();
        if (colorTimer > 20.f) {
            colorTimer -= 20.f;
            colorAmount -= 0.1f;
        }
        if (colorAmount <= 0.f) {
            isColored = false;
        }
    }
    for (auto & element : effects.get<9>()) {
        if (hitBox.overlapping(element.getHitBox()) && element.checkCanPoof()) {
            if (hp == 1) {
                element.disablePuff();
                element.setKillFlag();
            }
            element.poof();
            hp -= 1;
            isColored = true;
            colorAmount = 1.f;
        }
    }
    if (hp == 0) {
        killFlag = true;
        if (rng::random<4>() == 0) {
            effects.add<4>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
                           ::resHandlerPtr->getTexture(ResHandler::Texture::redglow),
                           xPos + 8, yPos + 10, Item::Type::Heart);
        } else {
            effects.add<5>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
                           ::resHandlerPtr->getTexture(ResHandler::Texture::blueglow),
                           xPos + 8, yPos + 10, Item::Type::Coin);
        }
        effects.add<2>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
                       ::resHandlerPtr->getTexture(ResHandler::Texture::fireExplosionGlow),
                       xPos + 12, yPos + 12);
    }
    switch (state) {
    case State::closed:
        if (std::sqrt(std::pow((xPos - player->getXpos() + 8), 2) + std::pow((yPos - player->getYpos() + 16), 2)) < 174) {
            state = State::opening;
            timer = 0;
            frameIndex = 0;
        }
        break;

    case State::opening:
        timer += elapsedTime.asMicroseconds();
        if (timer > 50000) {
            timer = 0;
            frameIndex += 1;
            if (frameIndex > 4) {
                frameIndex = 4;
                state = State::shoot1;
            }
        }
        break;

    case State::shoot1:
        target = player->requestFuturePos(TurretShot::lifetime * 1000);
        timer += elapsedTime.asMicroseconds();
        if (timer > 200000) {
            effects.add<0>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects), xPos, yPos + 8);
            effects.add<6>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
                           ::resHandlerPtr->getTexture(ResHandler::Texture::redglow),
                           xPos, yPos + 6, angleFunction(target.x + 16, target.y + 8, xPos + 18, yPos + 8));
            timer = 0;
            state = State::shoot2;
        }
        break;

    case State::shoot2:
        timer += elapsedTime.asMicroseconds();
        if (timer > 200000) {
            effects.add<0>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects), xPos, yPos + 8);
            effects.add<6>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
                           ::resHandlerPtr->getTexture(ResHandler::Texture::redglow),
                           xPos, yPos + 8, angleFunction(target.x + 16, target.y + 8, xPos + 18, yPos + 6));
            timer = 0;
            state = State::shoot3;
        }
        break;

    case State::shoot3:
        timer += elapsedTime.asMicroseconds();
        if (timer > 200000) {
            effects.add<0>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects), xPos, yPos + 8);
            effects.add<6>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
                           ::resHandlerPtr->getTexture(ResHandler::Texture::redglow),
                           xPos, yPos + 8, angleFunction(target.x + 16, target.y + 8, xPos + 18, yPos + 6));
            timer = 0;
            state = State::rest;
        }
        break;

    case State::rest:
        timer += elapsedTime.asMicroseconds();
        if (timer > 1200000) {
            if (std::sqrt(std::pow((xPos - player->getXpos() + 8), 2) + std::pow((yPos - player->getYpos() + 16), 2)) < 174) {
                state = State::shoot1;
            } else {
                state = State::closing;
            }
            timer = 0;
        }
        break;
        
    case State::closing:
        timer += elapsedTime.asMicroseconds();
        if (timer > 50000) {
            timer = 0;
            frameIndex -= 1;
            if (frameIndex < 0) {
                frameIndex = 0;
                state = State::closed;
            }
        }
        break;
    }
}

const Turret::HBox & Turret::getHitBox() const {
    return hitBox;
}

//Returns the turret's shadow sprite
const framework::Sprite & Turret::getShadow() {
    return shadowSheet[frameIndex];
}

bool Turret::getKillFlag() {
    return killFlag;
}

float Turret::getXpos() {
    return xPos;
}

float Turret::getYpos() {
    return yPos;
}

bool Turret::colored() {
    return isColored;
}

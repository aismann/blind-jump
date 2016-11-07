//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include <bitset>
#include <array>

#include "shutdownSignal.hpp"

class InputController {
public:
    InputController();
    void mapJsById();
    bool isFocused() const;
    bool pausePressed() const;
    bool leftPressed() const;
    bool rightPressed() const;
    bool upPressed() const;
    bool downPressed() const;
    bool shootPressed() const;
    bool actionPressed() const;
    void update(sf::RenderWindow &);
    void mapKeyboardKey(const sf::Keyboard::Key, const uint8_t);
    void mapJoystickButton(const uint32_t, const uint8_t);
    
private:
    enum {
        indexShoot,
        indexAction,
        indexPause,
        indexLeft,
        indexRight,
        indexUp,
        indexDown,
        indexFocused,
        indexCount
    };
    std::bitset<indexCount> keyMask;
    std::bitset<indexCount> joystickMask;
    std::array<uint32_t, 3> joystickMappings;
    std::array<sf::Keyboard::Key, 7> keyboardMappings;
};

//
//  FontController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/21/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//
//  This class is responsible for creating text for the current level and drawing it to the screen
//
//

#include "fontController.hpp"
#include "ResourcePath.hpp"
#include <iostream>

#define healthLimit 10

FontController::FontController(sf::View fontView, float x, float y) {
    // Store the view to use when drawing fonts
    this->fontView = fontView;
    
    windowCenterX = x;
    windowCenterY = y;

    // Load all of the game fonts into memory
    cornerstone.loadFromFile(resourcePath() + "Cornerstone.ttf");
    //const_cast<sf::Texture&>(cornerstone.getTexture(12)).setSmooth(false);
    
    // Set the waypoint text
    waypointText.setFont(cornerstone);
    std::string str = "Waypoint-1";
    waypointText.setString(str.c_str());
    waypointText.setCharacterSize(0.055 * fontView.getSize().y);
    waypointText.setPosition(16, 0);
    
    str = "Health:";
    healthText.setString(str.c_str());
    healthText.setCharacterSize(0.025 * fontView.getSize().y);
    healthText.setFont(cornerstone);
    
    str = "Blind Jump";
    titleText.setString(str.c_str());
    titleText.setCharacterSize(0.115 * fontView.getSize().y);
    titleText.setFont(cornerstone);
    titleText.setPosition(fontView.getSize().x / 2 - titleText.getLocalBounds().width / 2, fontView.getSize().y / 8);
    
    for (int i = 0; i < 10; i++) {
        // Load in score number textures
        healthFull[i].setRadius(10);
        healthFull[i].setFillColor(sf::Color::White);
        healthFull[i].setOutlineColor(sf::Color::White);
        healthFull[i].setOutlineThickness(3.5);
        healthEmpty[i].setRadius(10);
        healthEmpty[i].setFillColor(sf::Color::Transparent);
        healthEmpty[i].setOutlineColor(sf::Color::White);
        healthEmpty[i].setOutlineThickness(3.5);
    }
    
    health = 4;
    maxHealth = 4;
    score = 0;
}

void FontController::setWaypointText(int level) {
    // Put the health text in the right spot
    float initPos = fontView.getSize().x - maxHealth * 34 - 12;
    for (int i = 0; i < 10; i++) {
        healthFull[i].setPosition((i * 34) + initPos, 18);
        healthEmpty[i].setPosition((i * 34) + initPos, 18);
    }
    healthText.setPosition(initPos - 118, 10);
    captions.clear();
    std::string str = "Waypoint-";
    str += std::to_string(level);
    waypointText.setString(str.c_str());
}

void FontController::setZoneText(char zone) {
    switch (zone) {
        case 0:
            //zoneTextSpr.setTexture(zoneTextTxtr[0]);
            break;
            
        case 1:
            //zoneTextSpr.setTexture(zoneTextTxtr[1]);
            break;
            
        default:
            break;
    }
}

void FontController::print(sf::RenderWindow& window) {
    // Set the correct view, so not to blur the fonts
    window.setView(fontView);
    for (int i = 0; i < maxHealth; i++) {
        if (health > i) {
            window.draw(healthFull[i]);
        }
        else {
            window.draw(healthEmpty[i]);
        }
    }
    window.draw(waypointText);
    window.draw(healthText);
}

void FontController::update(sf::RenderWindow & window, float xOffset, float yOffset) {
    window.setView(fontView);
    if (!captions.empty()) {
        for (auto & element : captions) {
            // Update each element with the new offset information
            element.update(xOffset * ((fontView.getSize().x / 2) / windowCenterX), yOffset * ((fontView.getSize().y / 2) / windowCenterY));
            // If the object has text to display...
            if (!element.isClosed())
                window.draw(*element.getText());
        }
    }
}

void FontController::drawTitle(unsigned char alpha, sf::RenderWindow& window) {
    titleText.setColor(sf::Color(255, 255, 255, alpha));
    window.setView(fontView);
    window.draw(titleText);
}

sf::Text* FontController::getTitle() {
    return &titleText;
}

void FontController::updateHealth(char health) {
    // Set health equal to the input parameter or the max health, depending on which is lower
    this->health = std::min(health, maxHealth);
}

void FontController::terminateCaptions() {
    if (!captions.empty()) {
        for (auto & element : captions) {
            element.forceClose();
        }
    }
}

void FontController::updateMaxHealth(char health) {
    maxHealth = health;
    // Put the health in the right spot in the window
    float initPos = fontView.getSize().x - maxHealth * 34 - 12;
    for (int i = 0; i < 10; i++) {
        healthFull[i].setPosition((i * 34) + initPos, 18);
        healthEmpty[i].setPosition((i * 34) + initPos, 18);
    }
    healthText.setPosition(initPos - 42, 2);
}

char FontController::getMaxHealth() {
    return maxHealth;
}

void FontController::addCaption(float x, float y, const char * msg) {
    Caption cap(x * ((fontView.getSize().x / 2) / windowCenterX), y * ((fontView.getSize().y / 2) / windowCenterY), cornerstone);
    cap.setText(msg);
    cap.setWindowCenter(fontView.getSize().x / 2, fontView.getSize().y / 2);
    cap.setCharacterSize(0.025 * fontView.getSize().y);
    captions.push_back(cap);
}

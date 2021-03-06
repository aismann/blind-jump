#pragma once

#include "DetailGroup.hpp"
#include "GfxContext.hpp"
#include "HelperGroup.hpp"
#include "RenderType.hpp"
#include "alias.hpp"
#include "aspectScaling.hpp"
#include "backgroundHandler.hpp"
#include "camera.hpp"
#include "colors.hpp"
#include "effectsController.hpp"
#include "enemyController.hpp"
#include "framework/option.hpp"
#include "inputController.hpp"
#include "player.hpp"
#include "resourceHandler.hpp"
#include "soundController.hpp"
#include "tileController.hpp"
#include "userInterface.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <atomic>
#include <cmath>
#include <mutex>

class Game {
public:
    enum class TransitionState {
        None,
        ExitBeamEnter,
        ExitBeamInflate,
        ExitBeamDeflate,
        TransitionOut,
        TransitionIn,
        EntryBeamDrop,
        EntryBeamFade
    };
    Game(nlohmann::json & json);
    void updateLogic(const sf::Time &);
    void updateGraphics();
    void eventLoop();
    void nextLevel();
    int getLevel();
    DetailGroup & getDetails();
    enemyController & getEnemyController();
    tileController & getTileController();
    Player & getPlayer();
    EffectGroup & getEffects();
    SoundController & getSounds();
    InputController & getInputController();
    ui::Backend & getUI();
    ui::Frontend & getUIFrontend();
    Camera & getCamera();
    sf::Vector2f viewPort;
    TransitionState transitionState;
    sf::RenderWindow & getWindow();
    HelperGroup & getHelperGroup();

private:
    void init();
    bool hasFocus;
    sf::RenderWindow window;
    InputController input;
    SoundController sounds;
    Player player;
    Camera camera;
    ui::Backend UI;
    tileController tiles;
    EffectGroup effectGroup;
    DetailGroup detailGroup;
    HelperGroup helperGroup;
    enemyController en;
    ui::Frontend uiFrontend;
    std::mutex overworldMutex, UIMutex, transitionMutex;
    int level;
    bool stashed, preload;
    sf::Sprite vignetteSprite;
    backgroundHandler bkg;
    sf::Sprite vignetteShadowSpr;
    tileController::Tileset set;
    GfxContext gfxContext;
    sf::Sprite beamGlowSpr;
    sf::View worldView, hudView;
    sf::RenderTexture lightingMap;
    sf::RenderTexture target, secondPass, thirdPass, stash;
    sf::RectangleShape transitionShape, beamShape;
    void updateTransitions(const sf::Time &);
    void drawTransitions(sf::RenderWindow &);
    int_fast64_t timer;
};

// The first room is not procedurally generated so the positions of the walls
// need to be hard coded
// There may be a more efficient way to store this, but at O2 optimization clang
// and gcc convert the whole thing to an array of longs
extern const std::array<std::pair<float, float>, 59> levelZeroWalls;

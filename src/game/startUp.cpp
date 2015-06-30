//
// Created by Lukas on 12.04.2015.
//

#include <src/overlay/Overlay.h>
#include <src/overlay/Button.h>
#include "src/util/Window.h"
#include "src/util/ShaderProgram.h"
#include "src/renderer/Renderer.h"
#include "src/scene/Loader.h"
#include "startUp.h"
#include "Game.h"
#include "gameLoop/GameLoop.h"
#include "../tbs.h"
#include "util/ChanceSimulator.h"
#include "menu/Menu.h"
#include "menu/MenuLoop.h"

using namespace std;

int startUp(std::shared_ptr<EngineHelper> engine) {
	
    cout << "Creating new Game" << endl;
    std::shared_ptr<Game> game(new Game());
	
    std::cout << "FOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO 01" << std::endl;

    game->initGame();
	
    std::cout << "FOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO 02" << std::endl;

    cout << "First player: " << game->getPlayer(0)->getName() << endl;
    cout << "Second player: " << game->getPlayer(1)->getName() << endl;

    cout << "Creating Game Loop element" << endl;
    std::shared_ptr<GameLoop> loop(new GameLoop(game));
	
    //Setting up overlay
    game->setEngine(engine);
    game->createGameOverlay();

//#########################Setting Ground
    std::shared_ptr<mgf::Node> groundNode = engine->root->getChild("Assets.obj")->getChild("Ground")->clone();
    groundNode->translate(glm::vec3(20.0f, 0.f, -7.0f));
    groundNode->scale(glm::vec3(1.5f, 1.f, 1.5f));
    engine->actualScene->add(groundNode);

//######################### Setting up Overlay

    //###############################################  createSettingsOverlay overlay
//    std::shared_ptr<mgf::Overlay> overlay(new mgf::Overlay());
//
//    std::shared_ptr<mgf::Label> lab(new mgf::Label("mouse"));
//    lab->setBackground("res/images/Mouse.png");
//    lab->translate(glm::vec2(-10.f, -10.f));
//
//    overlay->add(lab);

//############ Setting up Playfield etc.

    game->setEngine(engine);


    game->setupField(engine->root, engine->actualScene, game->getFirstField());
    game->generateEnvironment();

    engine->actualScene->print();

    engine->w->use();
    engine->p->use();

    for (int i = 0; i < 2; ++i) {
        game->produceUnit("Infanterie", 0, false);
        game->produceUnit("Infanterie", 1, false);
        game->produceUnit("Artillerie", 0, false);
        game->produceUnit("Artillerie", 1, false);
        game->produceUnit("Kavallerie", 0, false);
        game->produceUnit("Kavallerie", 1, false);
    }

//#######Start Game
    loop->run(engine);

    return 0;

}
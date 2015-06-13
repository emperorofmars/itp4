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

using namespace std;




int startUp(){

    LOG_INIT("log/log_tbs.txt", true);

    LOG_F_TRACE(GAME_LOG_PATH, "Starting up ... ");


    cout << "creating new Game" << endl;
    std::shared_ptr<Game> game(new Game());


    game->initGame();

    cout << "first player: " << game->getPlayer(0)->getName() << endl;
    cout << "second player: " << game->getPlayer(1)->getName() << endl;


    cout << "creating Game Loop element" << endl;
    std::shared_ptr<GameLoop> loop(new GameLoop(game));

    //Setting up engine
    std::shared_ptr<EngineHelper> engine(new EngineHelper);

//#########################Setting Ground
    std::shared_ptr<mgf::Node> groundNode = engine->root->getChild("Assets.obj")->getChild("Ground")->clone();
    engine->actualScene->add(groundNode);


//#########################Setting up Overlay

    //###############################################  create overlay
    std::shared_ptr<mgf::Overlay> overlay(new mgf::Overlay());

//    std::shared_ptr<mgf::Button> but(new mgf::Button("but"));
//    but->setColor(glm::vec3(1.f, 0.5f, 0.5f));
//    but->setFont("res/fonts/main.ttf");
//    but->setText("blah");
//    but->setBackground("res/images/Button.png");

    std::shared_ptr<mgf::Label> lab(new mgf::Label("mouse"));
    lab->setBackground("res/images/Mouse.png");
    lab->translate(glm::vec2(-10.f, -10.f));

    //overlay->add(but);
    overlay->add(lab);



//############Setting up Playingfield etc.

    game->setEngine(engine);
    game->setupField(engine->root, engine->actualScene, game->getFirstField());




    engine->actualScene->print();




    engine->w->use();
    engine->p->use();

    for(int i = 0; i < 2; ++i) {
        game->produceUnit("Infanterie", 0);
        game->produceUnit("Infanterie", 1);
        game->produceUnit("Artillerie", 0);
        game->produceUnit("Artillerie", 1);
        game->produceUnit("Kavallerie", 0);
        game->produceUnit("Kavallerie", 1);
    }

//#######Start Game

    loop->run(engine);






    return 0;

}
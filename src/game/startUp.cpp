//
// Created by Lukas on 12.04.2015.
//

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




    std::shared_ptr<EngineHelper> engine(new EngineHelper);

    std::shared_ptr<mgf::Node> groundNode = engine->root->getChild("Assets.obj")->getChild("Ground")->clone();
    engine->actualScene->add(groundNode);

//    std::shared_ptr<mgf::Node> treeNode = engine->root->getChild("Assets.obj")->getChild("Tree")->clone();
//    engine->actualScene->add(treeNode);

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

    loop->run(engine);






    return 0;

}
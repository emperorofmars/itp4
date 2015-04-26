//
// Created by Lukas on 12.04.2015.
//

#include <src/util/Window.h>
#include <src/util/Input.h>
#include <src/util/ShaderProgram.h>
#include <src/util/Camera.h>
#include <src/renderer/Renderer.h>
#include <src/scene/Loader.h>
#include "startUp.h"
#include "Game.h"
#include "gameLoop/GameLoop.h"
#include "EngineHelper.h"

using namespace std;




int startUp(){






    cout << "creating new Game" << endl;
    std::shared_ptr<Game> game(new Game());


    game->initGame();



    cout << "first player: " << game->getPlayer(0)->getName() << endl;
    cout << "second player: " << game->getPlayer(1)->getName() << endl;


    cout << "creating Game Loop element" << endl;
    std::shared_ptr<GameLoop> loop(new GameLoop(game));



    LOG_INIT("log/log_tbs.txt", true);

    std::shared_ptr<EngineHelper> engine(new EngineHelper);


    game->setupField(engine->root, engine->actualScene, game->getFirstField());




    engine->actualScene->print();




    engine->w->use();
    engine->p->use();

    loop->run(engine);






    return 0;

}
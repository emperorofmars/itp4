
#include "tbs.h"
#include "game/startUp.h"
#include "libs/mlog.h"
#include "game/menu/MenuLoop.h"
#include "game/menu/Menu.h"

using namespace std;


int main(){

    cout << "Starting up Clash of Mages" << endl;
    cout << endl;

    std::shared_ptr<EngineHelper> engine(new EngineHelper);
//    engine->createMenuOverlay();

    Menu menu;
    menu.create(engine);

    MenuLoop menuLoop;
    menuLoop.run(engine);

    //startUp();

    return 0;
}

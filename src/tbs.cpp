
#include "tbs.h"
#include "game/startUp.h"
#include "libs/mlog.h"
#include "game/menu/MenuLoop.h"

using namespace std;


int main(){

    cout << "Starting up Clash of Mages" << endl;
    cout << endl;

    std::shared_ptr<EngineHelper> engine(new EngineHelper);
    engine->createMenuOverlay();

    MenuLoop menu;
    menu.run(engine);

    //startUp();

    return 0;
}

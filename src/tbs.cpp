
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

    Menu menu;
    menu.create(engine);    // creates menu overlay

    MenuLoop menuLoop;
    menuLoop.run(engine);   // starts menu loop

    return 0;
}

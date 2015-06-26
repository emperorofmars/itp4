
#include "tbs.h"
#include "game/startUp.h"
#include "libs/mlog.h"
#include "game/menu/MenuLoop.h"

using namespace std;


int main(){

    cout << "Starting up Clash of Mages" << endl;
    cout << endl;

    EngineHelper helper;
    helper.initMenu();

//    MenuLoop menu;
//    menu.init();

//    menu.run();

    //startUp();

    return 0;
}

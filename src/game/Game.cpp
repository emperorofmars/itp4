/*
** Author:  Lukas Stanek
** File:    Game.cpp
** Project: Turn Based Strategy Game
*/


#include "Game.h"

using namespace std;

void Game::initGame() {


    mPlayers[0].reset(new Player("Player1"));
    mPlayers[1].reset(new Player("Player2"));

    mPlayers[0]->setUnits(mUnitHolder1);
    mPlayers[1]->setUnits(mUnitHolder2);

    //mPlayers[0].setColor(vec4(1.0f,1.0f,0, 1.0f));
    //mPlayers[1].setColor(vec4(1.0f,0,1.0f, 1.0f));


    cout << "linking players... " << endl;
    mPlayers[0]->setNext(mPlayers[1]);
    mPlayers[1]->setNext(mPlayers[0]);


    cout << "getting instance of UnitManager" << endl;

    mUnitManager = UnitManager::getInstance();

    cout << "loading prototypes" << endl;
    mUnitManager->loadProtoypes();

    mUnitManager->printPrototypesToCout();



    generatePlayingField();





    mRounds = 1;
    mCurrentPlayer = 1;
    mStarted = time(0);


}


void Game::generatePlayingField() {

    cout << "generating playing field" << endl;

    std::vector< std::vector< shared_ptr<Hexfield> > > field;
    int size = 24;
    float SCALING = 2;

    field.resize(size);

    for(int i = 0; i<size; ++i){
        for(int j = 0; j < size; ++j){
            shared_ptr< Hexfield > newField(new Hexfield());

            newField->mPosition[0] = j*SCALING;
            newField->mPosition[1] = i*SCALING;

            if(i%2){
                newField->mPosition[0] += 0.5*SCALING;
            }

            newField->mPositionVector = glm::vec3(newField->mPosition[0], -10.f, newField->mPosition[1]);

            field[i].push_back(newField);
//            cout << field[i][j]->mPosition[0] << "/" << field[i][j]->mPosition[1] << " ";
        }
//        cout << endl;
    }

    cout << "field initialized" << endl;

    cout << "linking hexfields" << endl;

    for(int i = 0; i<size; ++i){
        for(int j = 0; j<size; ++j){
            shared_ptr<Hexfield> hexfield = field[i][j];

            //link to left
            if(j > 0){
                hexfield->linkedTo[5] = field[i][j-1];
//                cout << "linking "
//                << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                << " to " << field[i][j-1]->printPos() << endl;
            }else{
//                cout << "not linking left" << endl;
            }

            //link to right
            if(j<size-1){
                hexfield->linkedTo[2] = field[i][j+1];
//                cout << "linking "
//                << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                << " to " << field[i][j+1]->printPos() << endl;
            }else{
//                cout << "not linking right" << endl;
            }

            //decide if the line is even oder not
            if(!i%2){
                // EVEN ROW

                //link to top-left
                if(i>0 && j > 0){
                    hexfield->linkedTo[0] = field[i-1][j-1];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i-1][j-1]->printPos() << endl;
                }else{
//                    cout << "not linking top-left" << endl;
                }

                //link to top-right
                if(i>0){
                    hexfield->linkedTo[1] = field[i-1][j];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i-1][j]->printPos() << endl;
                }else{
//                    cout << "not linking top-right" << endl;
                }

                //link to bottom-right
                if(i < size-1){
                    hexfield->linkedTo[3] = field[i+1][j];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i+1][j]->printPos() << endl;
                }else{
//                    cout << "not linking bot-right" << endl;
                }

                //link to bottom-left
                if(i < size-1 && j > 0){
                    hexfield->linkedTo[4] = field[i+1][j-1];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " <<  field[i+1][j-1]->printPos() << endl;
                }else{
//                    cout << "not linking bot left" << endl;
                }

            }else{
                //UN-EVEN ROW

                //link to top-left
                if(i>0){
                    hexfield->linkedTo[0] = field[i-1][j];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i-1][j]->printPos() << endl;
                }else{
//                    cout << "not linking top-left" << endl;
                }

                //link to top-right
                if(i>0 && j<size-1){
                    hexfield->linkedTo[1] = field[i-1][j+1];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i-1][j+1]->printPos() << endl;
                }else{
//                    cout << "not linking top-right" << endl;
                }

                //link to bottom-right
                if(i < size-1 && j < size-1){
                    hexfield->linkedTo[3] = field[i+1][j+1];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i+1][j+1]->printPos() << endl;
                }else{
//                    cout << "not linking bot-right" << endl;
                }

                //link to bottom-left
                if(i < size-1){
                    hexfield->linkedTo[4] = field[i+1][j];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " <<  field[i+1][j]->printPos() << endl;
                }else{
//                    cout << "not linking bot-left" << endl;
                }
            }




//            cout << endl;
        }
    }
    cout << "linking complete" << endl;
    cout << endl;

    mFirstField = field[0][0];


    //Sets Position of Magetowers
    field[4][4]->setOccupation(std::shared_ptr<Unit>(mUnitManager->getChild("Magierturm")->clone()));
    field[19][19]->setOccupation(std::shared_ptr<Unit>(mUnitManager->getChild("Magierturm")->clone()));


}

int Game::setupField(std::shared_ptr<mgf::Node> root, std::shared_ptr<mgf::Node> actualScene,
                     std::shared_ptr<Hexfield> hexfield){

    cout << "setting up field nodes" << endl;

    std::shared_ptr<mgf::Node> newNode = root->getChild("hex.obj")->getChild("Hex")->clone();
    actualScene->add(newNode);
    newNode->translate(hexfield->mPositionVector);
    hexfield->setEngineObjectRef(newNode);

    hexfield->mIsRendered = 1;

    /**
     * This Loop will recursively call this method in every Hexfield
     */
    for(std::shared_ptr<Hexfield> field : hexfield->linkedTo){
        if(field && !field->mIsRendered){
            setupField(root, actualScene, field);
        }

    }


    if(std::shared_ptr<Unit> unit = hexfield->getOccupation()){
        if(unit->getName() == "Magierturm"){
            std::shared_ptr<mgf::Node> unitNode = root->getChild("scene.obj")->getChild("Cube")->clone();
            actualScene->add(unitNode);
            unitNode->translate(hexfield->mPositionVector);
            unitNode->rotate(90, glm::vec3(0.f, 1.f, 0.f));
            unitNode->scale(glm::vec3(0.3f, 3.f, 0.3f));

        }

    }


}


void Game::nextTurn() {
    mRounds++;
    //TODO if player > player size reset
    mCurrentPlayer++;

    std::shared_ptr<std::vector<std::shared_ptr<Unit>>> unitHolder = mPlayers[mCurrentPlayer]->mUnits;

    for(std::shared_ptr< Unit > unit : *unitHolder){
        unit->setRemainingMovement(unit->getMovement());
        unit->setTimesDefended(0);
    }


}

void Game::writeStatsToDb() {
    // TODO Write game stats to some persistent storage
}


/*
 * Setter & Getter
 */

shared_ptr<Player> Game::getPlayer(int i) {
    shared_ptr<Player> player;

    switch(i){
        case 0: player = mPlayers[0]; break;
        case 1: player = mPlayers[1]; break;
        default: player.reset(); break;
    }
    return player;
}

shared_ptr<Hexfield> Game::getFirstField() {
    return mFirstField;
}


//Game::state_t Game::do_state_default(std::shared_ptr<int> clicked) {
//    if(clicked == RIGHTCLICK){
//        return STATE_DEFAULT;
//    }
//
//    if(clicked == LEFTCLICK){
//
//    }
//
//
//    return STATE_SELECTED;
//}
//
//Game::state_t Game::do_state_selected(std::shared_ptr<int> clicked) {
//    if(clicked == RIGHTCLICK){
//        return STATE_DEFAULT;
//    }
//
//
//    return STATE_SELECTED;
//}

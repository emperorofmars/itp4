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

    //mPlayers[0].setColor(vec4(1.0f,1.0f,0, 1.0f));
    //mPlayers[1].setColor(vec4(1.0f,0,1.0f, 1.0f));


    cout << "linking players... " << endl;
    mPlayers[0]->setNext(mPlayers[1]);
    mPlayers[1]->setNext(mPlayers[0]);

    generatePlayingField();


    cout << "getting instance of UnitManager" << endl;

    mUnitManager = UnitManager::getInstance();

    cout << "loading prototypes" << endl;
    mUnitManager->loadProtoypes();

    mUnitManager->printPrototypesToCout();

}


void Game::generatePlayingField() {

    cout << "generating playing field" << endl;

    std::vector< std::vector< shared_ptr<Hexfield> > > field;
    int size = 24;

    field.resize(size);

    for(int i = 0; i<size; ++i){
        for(int j = 0; j < size; ++j){
            shared_ptr< Hexfield > newField(new Hexfield());

            newField->mPosition[0] = j;
            newField->mPosition[1] = i;

            if(i%2){
                newField->mPosition[0] += 0.5;
            }

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
    cout << "first field is " << mFirstField->mPosition[0] << " / " << mFirstField->mPosition[1] << endl;

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


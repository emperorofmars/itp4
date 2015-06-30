/*
** Author:  Lukas Stanek
** File:    Game.cpp
** Project: Turn Based Strategy Game
*/


#include <src/overlay/Button.h>
#include <src/scene/LightNode.h>
#include "Game.h"
#include "../tbs.h"
#include "states/Context.h"
#include "util/ChanceSimulator.h"
#include "menu/Menu.h"
#include "menu/MenuLoop.h"

using namespace std;

Game::Game() {
    mUnitHolder1.reset(new std::vector<std::shared_ptr<Unit>>);
    mUnitHolder2.reset(new std::vector<std::shared_ptr<Unit>>);
    SELECTED_STATE = false;
    mFieldSize = 24;
    quit = false;
    unitDmgCounter[0] = 0;
    unitDmgCounter[1] = 0;

    dmgedUnit[0].reset();
    dmgedUnit[1].reset();
}

Game::~Game() {
    mUnitHolder1.reset();
    mUnitHolder2.reset();
}

void Game::initGame() {


    mPlayers[0].reset(new Player("Player1"));
    mPlayers[1].reset(new Player("Player2"));

    mPlayers[0]->setId(0);
    mPlayers[1]->setId(1);

    mPlayers[0]->setUnits(mUnitHolder1);
    mPlayers[1]->setUnits(mUnitHolder2);

    //mPlayers[0].setColor(vec4(1.0f,1.0f,0, 1.0f));
    //mPlayers[1].setColor(vec4(1.0f,0,1.0f, 1.0f));


    cout << "linking players... " << endl;
    //mPlayers[0]->setNext(mPlayers[1]);
    //mPlayers[1]->setNext(mPlayers[0]);


    cout << "getting instance of UnitManager" << endl;

    mUnitManager = UnitManager::getInstance();

    cout << "loading prototypes" << endl;
    mUnitManager->loadProtoypes();

    mUnitManager->printPrototypesToCout();

    generatePlayingField();

    mRounds = 1;
    mCurrentPlayerId = 0;
    mStarted = time(0);
}


void Game::generatePlayingField() {

    cout << "generating playing field" << endl;

    std::vector<std::vector<shared_ptr<Hexfield> > > field;
    float SCALING = 2;

    field.resize(mFieldSize);

    for (int i = 0; i < mFieldSize; ++i) {
        for (int j = 0; j < mFieldSize; ++j) {
            shared_ptr<Hexfield> newField(new Hexfield());

            newField->mPosition[0] = j * SCALING;
            newField->mPosition[1] = i * SCALING;

            if (i % 2) {
                newField->mPosition[0] += 0.5 * SCALING;
            }

            newField->mPositionVector = glm::vec3(newField->mPosition[0], 0.f, newField->mPosition[1]);

            field[i].push_back(newField);
//            cout << field[i][j]->mPosition[0] << "/" << field[i][j]->mPosition[1] << " ";
        }
//        cout << endl;
    }

    cout << "field initialized" << endl;

    cout << "linking hexfields" << endl;

    for (int i = 0; i < mFieldSize; ++i) {
        for (int j = 0; j < mFieldSize; ++j) {
            shared_ptr<Hexfield> hexfield = field[i][j];

            //link to left
            if (j > 0) {
                hexfield->linkedTo[5] = field[i][j - 1];
//                cout << "linking "
//                << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                << " to " << field[i][j-1]->printPos() << endl;
            } else {
//                cout << "not linking left" << endl;
            }

            //link to right
            if (j < mFieldSize - 1) {
                hexfield->linkedTo[2] = field[i][j + 1];
//                cout << "linking "
//                << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                << " to " << field[i][j+1]->printPos() << endl;
            } else {
//                cout << "not linking right" << endl;
            }

            //decide if the line is even oder not
            if (i % 2 == 0) {
                // EVEN ROW

                //link to top-left
                if (i > 0 && j > 0) {
                    hexfield->linkedTo[0] = field[i - 1][j - 1];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i-1][j-1]->printPos() << endl;
                } else {
//                    cout << "not linking top-left" << endl;
                }

                //link to top-right
                if (i > 0) {
                    hexfield->linkedTo[1] = field[i - 1][j];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i-1][j]->printPos() << endl;
                } else {
//                    cout << "not linking top-right" << endl;
                }

                //link to bottom-right
                if (i < mFieldSize - 1) {
                    hexfield->linkedTo[3] = field[i + 1][j];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i+1][j]->printPos() << endl;
                } else {
//                    cout << "not linking bot-right" << endl;
                }

                //link to bottom-left
                if (i < mFieldSize - 1 && j > 0) {
                    hexfield->linkedTo[4] = field[i + 1][j - 1];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " <<  field[i+1][j-1]->printPos() << endl;
                } else {
//                    cout << "not linking bot left" << endl;
                }

            } else {
                //UN-EVEN ROW

                //link to top-left
                if (i > 0) {
                    hexfield->linkedTo[0] = field[i - 1][j];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i-1][j]->printPos() << endl;
                } else {
//                    cout << "not linking top-left" << endl;
                }

                //link to top-right
                if (i > 0 && j < mFieldSize - 1) {
                    hexfield->linkedTo[1] = field[i - 1][j + 1];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i-1][j+1]->printPos() << endl;
                } else {
//                    cout << "not linking top-right" << endl;
                }

                //link to bottom-right
                if (i < mFieldSize - 1 && j < mFieldSize - 1) {
                    hexfield->linkedTo[3] = field[i + 1][j + 1];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " << field[i+1][j+1]->printPos() << endl;
                } else {
//                    cout << "not linking bot-right" << endl;
                }

                //link to bottom-left
                if (i < mFieldSize - 1) {
                    hexfield->linkedTo[4] = field[i + 1][j];
//                    cout << "linking "
//                    << hexfield->mPosition[0] << "/" << hexfield->mPosition[1]
//                    << " to " <<  field[i+1][j]->printPos() << endl;
                } else {
//                    cout << "not linking bot-left" << endl;
                }
            }




//            cout << endl;
        }
    }
    cout << "linking complete" << endl;
    cout << endl;

    mFirstField = field[0][0];
    cout << "linking complete" << endl;


    //Sets Position of Magetowers
    std::shared_ptr<Unit> tower(mUnitManager->getChild("Magierturm")->clone());
    mPlayers[0]->setBase(tower);
    field[4][4]->setOccupation(tower);
    tower->setCurrentHexfield(field[4][4]);
    tower->setOwner(0);

    std::shared_ptr<Unit> tower2(mUnitManager->getChild("Magierturm")->clone());
    mPlayers[1]->setBase(tower2);
    field[19][19]->setOccupation(tower2);
    tower2->setCurrentHexfield(field[19][19]);
    tower2->setOwner(1);

//    LOG_F_TRACE(GAME_LOG_PATH, "player 1 base : ", mPlayers[0]->getBase()->getCurrentHexfield()->printPos());
//    LOG_F_TRACE(GAME_LOG_PATH, "player 2 base: ", mPlayers[1]->getBase()->getCurrentHexfield()->printPos());

}

int Game::setupField(std::shared_ptr<mgf::Node> root, std::shared_ptr<mgf::Node> actualScene,
                     std::shared_ptr<Hexfield> hexfield) {

    //cout << "setting up field nodes" << endl;

    std::shared_ptr<mgf::Node> newNode = root->getChild("Assets.obj")->getChild("Hex")->clone();
    actualScene->add(newNode);
    newNode->translate(hexfield->mPositionVector);
    hexfield->setEngineObjectRef(newNode);

    hexfield->mIsRendered = 1;

    /**
     * This Loop will recursively call this method in every Hexfield
     */
    for (std::shared_ptr<Hexfield> field : hexfield->linkedTo) {
        if (field && !field->mIsRendered) {
            setupField(root, actualScene, field);
        }

    }


    if (std::shared_ptr<Unit> unit = hexfield->getOccupation()) {
        if (unit->getName() == "Magierturm") {
            std::shared_ptr<mgf::Node> unitNode;
            if(unit->getOwner() == 0){
                unitNode = root->getChild("Assets.obj")->getChild("Tower02")->clone();

            }else{
                unitNode = root->getChild("Assets.obj")->getChild("Tower01")->clone();

            }
            //std::shared_ptr<mgf::Node> unitNode = root->getChild("scene.obj")->getChild("Cube")->clone();
            unit->setUnitNode(unitNode);
            actualScene->add(unitNode);
            unitNode->translate(hexfield->mPositionVector);
            //unitNode->rotate(90, glm::vec3(0.f, 1.f, 0.f));
            //unitNode->scale(glm::vec3(0.6f, 0.6f, 0.6f));

        } else if (unit->getName() == "Infanterie") {
            std::shared_ptr<mgf::Node> unitNode = root->getChild("Assets.obj")->getChild("Infantry")->clone();
            unit->setUnitNode(unitNode);
            actualScene->add(unitNode);
            unitNode->translate(hexfield->mPositionVector);
            unitNode->scale(glm::vec3(.5f, .5f, .5f));

        }

    }

}


void Game::nextTurn() {
    mRounds++;

    getPlayer(mCurrentPlayerId)->setCam(engine->cam->getPos());

    //setting Player
    mCurrentPlayerId++;
    if (mCurrentPlayerId == 2) mCurrentPlayerId = 0;

    std::shared_ptr<Player> player = getPlayer(mCurrentPlayerId);

    glm::vec3 base = player->getBase()->getCurrentHexfield()->mPositionVector;

    cout << " player cam : " << mgf::vec3_toStr(player->getCam()) << endl;
    if(player->getCam()[0] != -1
            && player->getCam()[1] != -1
            && player->getCam()[2] != -1){
        engine->cam->setPos(player->getCam());
    }else{
        engine->cam->setPos(glm::vec3(base[0], engine->cam->getPos()[1], base[2] + 25.f));

    }

    LOG_F_TRACE(GAME_LOG_PATH, "current Player id : ", mCurrentPlayerId);

    setPlayerStatus();

    if (getSelectedState()) {
        deselectUnit();
    }
    Context::getInstance()->setCurrentState(States::STATE_IDLE);

    //resetting units of Current Player
    std::shared_ptr<std::vector<std::shared_ptr<Unit >>> unitHolder = mPlayers[mCurrentPlayerId]->mUnits;
    for (std::shared_ptr<Unit> unit : *unitHolder) {
        unit->setRemainingMovement(unit->getMovement());
        unit->setTimesDefended(0);
    }

}

void Game::produceUnit(std::string unitName, int playerId, bool useMana) {
    std::shared_ptr<Unit> newUnit = mUnitManager->getChild(unitName)->clone();
    if (!newUnit) {
        return;
    }
    newUnit->setOwner(playerId);

    std::shared_ptr<Unit> mageTower = getPlayer(playerId)->getBase();
    std::shared_ptr<Hexfield> currentField = mageTower->getCurrentHexfield();

    std::shared_ptr<Hexfield> destinedField = getNextFreeField(currentField);
    if (destinedField == NULL) return;

    //checks Mana and subtracts
    if (useMana && !getPlayer(playerId)->useMana(newUnit->getManaCost())) {
        LOG_F_TRACE(GAME_LOG_PATH, "Not enough Mana ", getPlayer(playerId)->getCurMana());
        setPlayerStatus();
//        engine->mana->setText(std::to_string(getPlayer(playerId)->getCurMana()));
        return;
    } else {
        setPlayerStatus();
//        engine->mana->setText(std::to_string(getPlayer(playerId)->getCurMana()));
        LOG_F_TRACE(GAME_LOG_PATH, "Mana left ", getPlayer(playerId)->getCurMana());
    }

    LOG_F_TRACE(GAME_LOG_PATH, "target Player: ", playerId, " base hex found at: ", currentField->mPosition[1], "/",
                currentField->mPosition[0]);
    LOG_F_TRACE(GAME_LOG_PATH, "Model to Use ", newUnit->getModel());
    string playerString = std::to_string(playerId+1);
    playerString.insert(playerString.begin(), '0');
    cout << " player " << playerString << endl;
    std::shared_ptr<mgf::Node> unitNode = engine->root->getChild("Assets.obj")->getChild(newUnit->getModel().append(playerString))->clone();
    newUnit->setUnitNode(unitNode);
    newUnit->setCurrentHexfield(destinedField);
    destinedField->setOccupation(newUnit);
    getPlayer(playerId)->getUnits()->push_back(newUnit);


    engine->actualScene->add(unitNode);
    //unitNode->scale(glm::vec3(.5f, .5f, .5f));
    unitNode->setTranslation(destinedField->mPositionVector);
    //TODO set COLOR / MATERIAL for unit -> owner specific




}

std::shared_ptr<Hexfield> Game::getNextFreeField(std::shared_ptr<Hexfield> currentField) {
    for (std::shared_ptr<Hexfield> hex : currentField->linkedTo) {
        if (!hex->getIsOccupied()) {
            return hex;
        }
    }

    return NULL;
}

int Game::unitMovementWrapper(std::shared_ptr<Unit> unit,
                              std::shared_ptr<Hexfield> destination) {
    LOG_F_TRACE(GAME_LOG_PATH, "Starting unit movement ", unit->getName(), " to ",
                destination->mPosition[1], "/", destination->mPosition[0]);

    std::shared_ptr<Hexfield> startField = unit->getCurrentHexfield();


    std::shared_ptr<Hexfield> finishedField = unit->moveTo(unit);

    LOG_F_TRACE(GAME_LOG_PATH, "translating unit to endpoint");
    if (finishedField) {
        //LOG_F_TRACE(GAME_LOG_PATH, finishedField->mPositionVector);
        std::shared_ptr<mgf::Node> node = unit->getUnitNode();
        finishedField->mPositionVector;
        LOG_F_TRACE(GAME_LOG_PATH, finishedField->mPosition[1], "/", finishedField->mPosition[0]);

        unit->getUnitNode()->setTranslation(finishedField->mPositionVector);

    }

}


int Game::cleanUp() {
//    writeStatsToDb();

    deleteUnits();

    mPlayers[0].reset();

    mPlayers[1].reset();

    mWinner.reset();
    mSelectedUnit.reset();

    eraseField(mFirstField);
    mFirstField.reset();

    delete(mUnitManager);




    return 0;
}

int Game::deleteUnits() {

    for (int i = 0; i < mUnitHolder1->size(); ++i) {
        std::shared_ptr<Unit> currentUnit = mUnitHolder1->at(i);
        currentUnit->getCurrentHexfield()->setEmtpy();
        mUnitHolder1->at(i).reset();
        currentUnit.reset();
    }

    for (int i = 0; i < mUnitHolder2->size(); ++i) {
        std::shared_ptr<Unit> currentUnit = mUnitHolder2->at(i);
        currentUnit->getCurrentHexfield()->setEmtpy();
        mUnitHolder2->at(i).reset();
        currentUnit.reset();
    }

    mUnitHolder1.reset();
    mUnitHolder2.reset();
}

int Game::eraseField(std::shared_ptr<Hexfield> hex) {
    for (int i = 0; i < mFieldSize; ++i) {
        deleteRow(hex);
        if (i % 2 == 0) {
            hex = hex->linkedTo[3];
        } else {
            hex = hex->linkedTo[4];
        }
    }
}

void Game::deleteRow(std::shared_ptr<Hexfield> firstField) {
    if (firstField->linkedTo[2] != NULL) {
        deleteRow(firstField->linkedTo[2]);
        deleteAllLinks(firstField->linkedTo[2]);
    }
}


void Game::deleteAllLinks(std::shared_ptr<Hexfield> hex) {
    for (int i = 0; i < 6; ++i) {
        hex->linkedTo[i].reset();
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

    switch (i) {
        case 0:
            player = mPlayers[0];
            break;
        case 1:
            player = mPlayers[1];
            break;
        default:
            player.reset();
            break;
    }
    return player;
}

std::shared_ptr<Hexfield> Game::getHexAt(std::shared_ptr<Hexfield> current, float x, float y) {
    float minDist;
    float curDist;
    std::shared_ptr<Hexfield> nearest(current);

//LOG_F_TRACE(GAME_LOG_PATH, "in field: ", current->mPosition[1], "/", current->mPosition[0]);

    minDist = abs(x - current->mPosition[1])
              + abs(y - current->mPosition[0]);

    for (
        std::shared_ptr<Hexfield> neighbor :
            current->linkedTo) {
        if (neighbor == NULL) continue;

        curDist = abs(x - neighbor->mPosition[1]) + abs(y - neighbor->mPosition[0]);
        if (curDist < minDist) {
            minDist = curDist;
            nearest = neighbor;
        }

    }

    if (nearest == current) {
        LOG_F_TRACE(GAME_LOG_PATH, "Found nearest at ", current->mPosition[1], "/", current->mPosition[0]);
        return
                current;
    } else {
        nearest = getHexAt(nearest, x, y);
    }

    return
            nearest;
}


shared_ptr<Hexfield> Game::getFirstField() {
    return mFirstField;
}


bool Game::getSelectedState() {
    return SELECTED_STATE;
}

void Game::setSelectedState(bool selectedState) {
    SELECTED_STATE = selectedState;
}

std::shared_ptr<Unit> Game::getSelectedUnit() {
    return mSelectedUnit;
}

void Game::selectUnit(shared_ptr<Unit> ptr) {
    mSelectedUnit = ptr;

    setStatusBar();

    std::shared_ptr<mgf::Material> newmat(new mgf::Material);
    newmat->mDiffuseColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
    getSelectedUnit()->getUnitNode()->setMaterial(newmat);
    //actualScene->getChild("Cube")->resetMaterial();


    SELECTED_STATE = true;
}

int Game::getCurrentPlayerId() {
    return mCurrentPlayerId;
}

void Game::setEngine(std::shared_ptr<EngineHelper> engine) {
    this->engine = engine;
}

std::shared_ptr<Hexfield> Game::getHexAtMousePos() {
    glm::vec3 pos = engine->getMousePos();
    return getHexAt(getFirstField(), pos[2], pos[0]);
}

void Game::deselectUnit() {
    getSelectedUnit()->getUnitNode()->resetMaterial();
    mSelectedUnit.reset();
    SELECTED_STATE = false;

    cleanStatusBar();
}

std::shared_ptr<mgf::IOverlayElement> Game::getOverlayInteraction() {
    return engine->getOverlayOnPos();
}

void Game::quitGame() {
    quit = true;
}

bool Game::getQuit() {
    return quit;
}

void Game::generateEnvironment() {
    std::shared_ptr<ChanceSimulator> randomGenerator = ChanceSimulator::getInstance();

    for (int i = 0; i < 400; ++i) {
        float x = randomGenerator->getRandomCoord();
        float y = randomGenerator->getRandomCoord();

        if ((x > 0 && x < 47) && (y > 0 && y < 47)) {
            continue;
        }

        float scalingVector = 1.f;

        scalingVector = randomGenerator->getRandomFloat(0.5f, 1.5f);

        std::shared_ptr<mgf::Node> tree = engine->root->getChild("Assets.obj")->getChild("Tree")->clone();
        tree->scale(glm::vec3(scalingVector, scalingVector, scalingVector));
        tree->translate(glm::vec3(x, 0.f, y));
        tree->add(engine->root->getChild("Assets.obj")->getChild("defaultobject")->clone());

        engine->actualScene->add(tree);
        engine->player->setText(getPlayer(mCurrentPlayerId)->getName());
    }
}

/**
 * Sets health in the status bar according to selected unit
 */
void Game::setStatusBar() {
    if (engine->health != NULL) {
        engine->health->setText(std::to_string(getSelectedUnit()->getCurHp()));
    }
}

/**
 *  Clears health in status bar
 */

void Game::cleanStatusBar() {
    if (engine->health != NULL) {
        engine->health->setText("");
    }
}

/**
 * Sets Player name and current Mana in the status bar
 */
void Game::setPlayerStatus() {
    engine->player->setText(getPlayer(mCurrentPlayerId)->getName());
    engine->mana->setText(std::to_string(getPlayer(mCurrentPlayerId)->getCurMana()));
}

/**
 * Cleans player status
 */
void Game::cleanPlayerStatus() {
    engine->player->setText("");
    engine->mana->setText("");
}

void Game::resetStatusBar() {
    engine->player.reset();
    engine->mana.reset();
    engine->health.reset();
}

void Game::createGameOverlay() {
//    printStatus(1, "game overlay");

    engine->actualScene.reset(new mgf::Node("gameScene"));
    engine->overlay.reset(new mgf::Overlay());

    /*
     * Create buttons
     */
    float x = 0.0;
    float y = 0.0;

    std::shared_ptr <mgf::Button> quitBtn(new mgf::Button("quitBtn"));
    quitBtn->setBackground("res/images/elemente/quit.png");
    x = (0.92f/engine->w->getAspectRatio() + quitBtn->getScale()[0]);
    y = (0.06f/engine->w->getAspectRatio() + quitBtn->getScale()[1]);
    std::cout << "Quit button coordinates: " << x << "x" << y << std::endl;
    quitBtn->translate(glm::vec2(x, y));

    std::shared_ptr <mgf::Button> endTurnBtn(new mgf::Button("endTurnBtn"));
    endTurnBtn->setBackground("res/images/elemente/nextround.png");
    y = (0.94f/engine->w->getAspectRatio() + endTurnBtn->getScale()[1]);
    std::cout << "Next turn button coordinates: " << x << "x" << y << std::endl;
    endTurnBtn->translate(glm::vec2(x, y));

    std::shared_ptr <mgf::Button> createInfantry(new mgf::Button("infantryBtn"));
    createInfantry->setBackground("res/images/elemente/infantry.png");
    std::cout << "Window Aspect Ratio: " << engine->w->getAspectRatio() << std::endl
    << "Scale: " << createInfantry->getScale()[0];
//    exit(1);
    x = ((1/engine->w->getAspectRatio()) + createInfantry->getScale()[0]);
    x -= 0.94;
    std::cout << "Create infantry coordinates: " << x << "x" << y << std::endl;
    createInfantry->translate(glm::vec2(x, y));
//    exit(1);

    std::shared_ptr <mgf::Button> createCavalry(new mgf::Button("cavalryBtn"));
    createCavalry->setBackground("res/images/elemente/cavalry.png");
    x += 0.1f;
    createCavalry->translate(glm::vec2(x, y));

    std::shared_ptr <mgf::Button> createArtillery(new mgf::Button("artilleryBtn"));
    createArtillery->setBackground("res/images/elemente/artillery.png");
    x += 0.1f;
    createArtillery->translate(glm::vec2(x, y));

    /*
     * Create game status Labels:
     */

    // Health
    std::shared_ptr <mgf::Label> statusHealth(new mgf::Label("statusHealth"));
    statusHealth->setBackground("res/images/elemente/health.png");
    x = -0.05f;
    y = -0.05f;
    statusHealth->translate(glm::vec2(x,y));

    // Player
    engine->player.reset(new mgf::Label("label"));
    engine->player->setFont("res/fonts/main.ttf");
    engine->player->setBackground("res/images/elemente/transparent.png");
    engine->player->setColor(glm::vec3(265,165,0));
    engine->player->translate(glm::vec2(x+0.01, 0.01));

    engine->health.reset(new mgf::Label("health"));
    engine->health->setFont("res/fonts/main.ttf");
    engine->health->setBackground("res/images/elemente/transparent.png");
    engine->health->setColor(glm::vec3(265,165,0));
    engine->health->translate(glm::vec2(0.05f, y-0.01));

    // Mana
    std::shared_ptr <mgf::Label> statusMana(new mgf::Label("statusMana"));
    statusMana->setBackground("res/images/elemente/mana.png");
    statusMana->translate(glm::vec2(0.3, y));

    engine->mana.reset(new mgf::Label("mana"));
    engine->mana->setFont("res/fonts/main.ttf");
    engine->mana->setBackground("res/images/elemente/transparent.png");
    engine->mana->setColor(glm::vec3(265,165,0));
    engine->mana->translate(glm::vec2(0.37f, y-0.01));

    /*
     * Add elements to Overlay
     */
    engine->overlay->add(createInfantry);
    engine->overlay->add(createCavalry);
    engine->overlay->add(createArtillery);
    engine->overlay->add(quitBtn);
    engine->overlay->add(endTurnBtn);
    engine->overlay->add(statusHealth);
    engine->overlay->add(engine->health);
    engine->overlay->add(statusMana);
    engine->overlay->add(engine->mana);
    engine->overlay->add(engine->player);
    engine->overlay->add(engine->pointer);

//#### Setting up Sunlight
    std::shared_ptr<mgf::Node> light(new mgf::LightNode("sun"));
    light->setLight(mgf::SUN_LIGHT, 2, 2, glm::vec3(1.f, 1.f, 1.f), glm::vec3(5.f, 15.f, 15.f), glm::vec3(0.f, -10.f, -5.f), 30);
    engine->actualScene->add(light);

//    printStatus(2, "game overlay");
}
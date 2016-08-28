#include "GameController.h"


void GameController::play(){
    //cout << "Start Play" << endl;
    while(cb->getRecentOpponentMove().getStatus() == Constants::EMPTY || !cb->isGameOver()){
        //cout << "turn " << endl;
        if(currentPlayer == Constants::USER){
            cb->dropBomb(userbot->calculateNextMove(*cb),Constants::USER);
            currentPlayer = Constants::COMP;
        }
        else{
            cb->dropBomb(compbot->calculateNextMove(*cb),Constants::COMP);
            currentPlayer = Constants::USER;
        }
    }
    fstream f(Constants::filename.c_str(),ios::in | ios::out | ios::app);
    f << "\n\t\"winner\" : \"" << ((cb->getRecentOpponentMove().getStatus() == Constants::BOMB) ? Constants::userbotname : Constants::compbotname) << "\"\n}";
    //cout << "End Play" << endl;
}

//initial toss to decide which bot plays first
bool GameController::toss(){
    srand(time(NULL));
    return rand()%2;
}


GameController::GameController(){
    //cout << "Game Controller Created" << endl;
    if(toss()){
        currentPlayer = Constants::USER;
    }
    else{
        currentPlayer = Constants::COMP;
    }

    userbot = new UserBot(Constants::USER);
    compbot = new CompBot(Constants::COMP);
    cb = new NuclearReactor();

    play();
}
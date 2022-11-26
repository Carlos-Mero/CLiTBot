// this is the basic version of the project which only fulfills the least tasks of the whole project.

#include "struct.h"
#include "const.h"

int main_bs(){
    // This is the entrance of the standard version of the game, and will be called in main.cpp.
    
    Game game(cst::SAVE_PATH, cst::CMD_LIM);
    
    while(game.is_running()){
        game.process();
    }
    
    return 0;
}

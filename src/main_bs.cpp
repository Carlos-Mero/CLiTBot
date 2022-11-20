// this is the basic version of the project which only fulfills the least tasks of the whole project.


#include "struct.h"
#include "interaction.cpp"
#include "runtime.cpp"
#include "imgdraw.cpp"

int main_bs(){
    // This is the entrance of the standard version of the game, and will be called in main.cpp.
    
    Game game;
    
    while(game.is_running()){
        game.process();
    }
    
    return 0;
}

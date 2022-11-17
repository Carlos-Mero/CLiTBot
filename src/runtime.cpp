// This is the module that reads from the input and runs the whole game.

#include "struct.h"

void Map::light_lit(Position & pos){
    // This function is called when the player uses the "LIT" command.
    // This will light the light at that position, and decreases the light_count by 1.
    
    m_light_count--;
    return;
}

void Game::set_map(){
    // This method loads the map into the game class.
    // Use the "new" operator and construct a map object, then assign the pointer to it to the variable m_map.
    
    return;
}

void Game::set_bot(){
    // This will set a value of the variable m_bot, just like what the function above does.
    
    return;
}

void Game::process(){
    // This is the main function running behind the game loop.
    // It will need the cooperation of all three modules of the game.
    // In this function we may need to call many other methods of the class Game.
    // All variables in this game will be updated here in this method.
    
    return;
}

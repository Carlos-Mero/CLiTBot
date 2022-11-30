// This is the module that reads from the input and runs the whole game.

#include "struct.h"
#include "const.h"
#include <iostream>

// MARK: Standard features

void Bot::move(){
    // This function moves the bot.
    
    return;
}

void Bot::turn(Direction d){
    // This function changes the direction of the bot.
    
    if (d == left) {
        switch (m_dir) {
            case up:
                m_dir = left;
                break;
            case left:
                m_dir = down;
                break;
            case down:
                m_dir = right;
                break;
            case right:
                m_dir = up;
                break;
                
            default:
                break;
        }
    }else if (d == right){
        switch (m_dir) {
            case up:
                m_dir = right;
                break;
            case left:
                m_dir = up;
                break;
            case down:
                m_dir = left;
                break;
            case right:
                m_dir = down;
                break;
                
            default:
                break;
        }
    }else{
        std::cout << "发生了一些错误，无法处理转向方向" << std::endl;
    }
    
    return;
}

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

// MARK: Extended features

void Ex_game::ex_process(){
    
    if (main_window->ShouldClose()) {
        m_running = false;
    }
    
    mouse_pos = raylib::Mouse::GetPosition();
    
    if (help_background->CheckCollision(mouse_pos)) {
        help_background_color = cst::raylightblue;
        if (raylib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
            help_index++;
        }
    }else {
        help_background_color = cst::rayblue;
    }
    
    if (IsKeyPressed(KEY_SPACE)) {
        start_index++;
    }
    
    return;
}

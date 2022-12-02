// This is the module that reads from the input and runs the whole game.

#include "struct.h"
#include "const.h"
#include <iostream>
#include <stdio.h>

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

// MARK: Initializer for the interface

void Ex_game::grid_init(){
    
    ver_line_0 = new raylib::Rectangle(cst::ver_line_0_pos, cst::ver_line_0_size);
    
    ver_line_1 = new raylib::Rectangle(cst::ver_line_1_pos, cst::ver_line_1_size);
    
    hor_line_0 = new raylib::Rectangle(cst::hor_line_0_pos, cst::hor_line_0_size);
    
    hor_line_1 = new raylib::Rectangle(cst::hor_line_1_pos, cst::hor_line_1_size);
    
    game_space = new raylib::Rectangle(cst::game_view_pos, cst::game_view_size);
    
    text_space = new raylib::Rectangle(cst::text_space_pos, cst::text_space_size);
    
    dynamic_curser = new raylib::Rectangle(cst::dynamic_cursor_start_pos, cst::dynamic_cursor_size);
    
    help_background = new raylib::Rectangle(cst::help_background_pos, cst::help_background_size);
    
    help_text_color = RAYWHITE;
    
    help_background_color = cst::rayblue;
    
    help_index = 0;
    
    start_index = true;
    
    frame_count = 0;
    
    text_selected = 1;
    
    input_chars[10] = '\0';
    
    input_count = 0;
    
    command_list_index = 0;
    
    return;
}

// MARK: Input handler

void Ex_game::input_process(){
    
    int key = GetCharPressed();
    
    while (key > 0) {
        
        if ((key >= 32) && (key <= 125) && (input_count < cst::message_max_len)) {
            
            input_chars[input_count] = (char)key;
            input_count++;
            input_chars[input_count] = '\0';
            
        }
        key = GetCharPressed();
    }
    
    if (IsKeyPressed(KEY_BACKSPACE) && input_count > 0) {
        
        input_count--;
        input_chars[input_count] = '\0';
        
    } else if (IsKeyPressed(KEY_BACKSPACE) && input_count == 0) {
        
        input_chars[input_count] = '\0';
        
    } else if (IsKeyPressed(KEY_ENTER) && input_count > 0){
        
        strcpy(command_lists[command_list_index%cst::CMD_list_max_len], input_chars);
        command_list_index++;
        input_count = 0;
        input_chars[input_count] = '\0';
        
    }
    
    dynamic_curser->SetPosition(cst::dynamic_cursor_start_pos.GetX() + MeasureText(input_chars, 18), dynamic_curser->GetY());
    
    return;
}

// MARK: Ex_process workflow

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
        start_index = false;
    }
    
    if (text_space->CheckCollision(mouse_pos) && raylib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
        text_selected = 1;
    }
    
    if (!text_space->CheckCollision(mouse_pos) && raylib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
        text_selected = 0;
    }
    
    if (frame_count/32 % 2 && text_selected) {
        dynamic_curser->Draw(cst::rayblue);
    }
    
    if (text_selected) {
        input_process();
    }
    
    frame_count++;
    
    return;
}

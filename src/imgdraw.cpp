// this is the module that draws and outputs the map of the game.

#include "struct.h"
#include "const.h"
#include <fstream>
#include <iostream>
#include <string>

void Game::op_map(){
    // This function draws and saves the map of the game.
    std::ofstream mapfile;
    mapfile.open(cst::SAVE_PATH + "save.bmp", std::ios::binary);
    // Warning! This method will open the file and wipe all the content existing there! But for our purpose of saving the map, it's just fine.
    
    if(!mapfile.is_open()){
        mapfile.close();
        std::cout << "发生了一些意外……文件没能正常打开？！" << std::endl;
        return;
    }
    
    mapfile.write((char *)&cst::BFH, sizeof(cst::BFH));
    mapfile.write((char *)&cst::BIH, sizeof(cst::BIH));
    // Here we write in the header of the picture.
    
    for(int y = cst::SCREEN_HEIGHT-1; y >= 0; y--){
        for(int x = 0; x < cst::SCREEN_WIDTH-cst::WIDGET_WIDTH; x++){
            pix p = {0, 0, 0};
            mapfile.write((char *)&p, sizeof(p));
        }
    }
    
    /*Position plt_st = m_bot->current_position();
    plt_st.x -= cst::SCREEN_WIDTH / 2;
    plt_st.y -= cst::SCREEN_HEIGHT / 2;*/
    // Set the position of the bot as the center of the whole picture.
    
    mapfile.close();
    
    std::cout << "当前地图输出成功！" << std::endl;
    
    return;
}

void Game::auto_op_map(){
    // This function automatically saves and outputs the condition of the map.
    
    return;
}

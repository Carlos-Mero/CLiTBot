// this is the basic version of the project which only fulfills the least tasks
// of the whole project.

#include "const.h"
#include "struct.h"
#include <iostream>

int main_bs() {
    // This is the entrance of the standard version of the game, and will be
    // called in main.cpp.

    Game *game = new Game(cst::SAVE_PATH, cst::CMD_LIM);
    
    std::cout << "欢迎来到CLiTBot！" << std::endl;
    std::cout << "请输入指令 LOAD <MAP_PATH> 选择一张地图并开始游戏"
              << std::endl;
    std::cout << "有需要时也可以输入 HELP 以查询更多帮助" << std::endl;

    while (game->is_running()) {
        game->process();
    }

    delete game;

    return 0;
}

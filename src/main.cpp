// This is the main entrance of CLiTBot, a project of the course "Fundamental of
// Programming". There're Three members here in our group, They are Yu Zhan,
// Huang Yanxing and Wang Yuhan. Thanks for all!

#include "modes.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    // This is the main entrance of the game CLiTBot, we can choose between both
    // basic version and extended version of the game here through a graphic
    // user interface.

    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    // This accelerates the iostream of the whole game.

    std::cout << "游戏启动成功！" << std::endl;
    std::cout << "你想要启用的游戏模式是？" << std::endl;

start:
    std::cout << "标准版...输入\"CLI\"" << std::endl;
    std::cout << "豪华版...输入\"GUI\"" << std::endl;

    std::string type;
    std::cin >> type;

    if (type == "CLI") {
        main_bs();
    } else if (type == "GUI") {
        main_ex();
    } else {
        std::cout << "抱歉我没听懂，请问您想要启用的游戏模式是？" << std::endl;
        goto start;
    }

    return 0;
}

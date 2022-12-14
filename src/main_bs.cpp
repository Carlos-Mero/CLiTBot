// this is the basic version of the project which only fulfills the least tasks
// of the whole project.

#include "const.h"
#include "struct.h"

int main_bs() {
  // This is the entrance of the standard version of the game, and will be
  // called in main.cpp.

  Game *game = new Game(cst::SAVE_PATH, cst::CMD_LIM);

  while (game->is_running()) {
    game->process();
  }

  delete game;

  return 0;
}

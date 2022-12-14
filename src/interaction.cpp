// This is the module that interacts with the user.

#include "const.h"
#include "struct.h"
#include <fstream>
#include <iostream>

// MARK: Standard features

void Game::cin_cmd() {
  // This function handles the interaction with the player.
  // It recieves the command and send it to the process method.

  return;
}

void Game::op_info() {
  // This function handles the output of the information due to the command sent
  // in.

  return;
}

// MARK: Extended features

void Ex_game::show_help_window() {

  help_text->Draw(cst::game_view_pos.GetX() + 8.0f,
                  cst::game_view_pos.GetY() + 5.0f);

  return;
}

void Ex_game::show_start_window() {

  DrawText(TextSubtext(cst::start_message, 0, frame_count / 4), 340, 190, 26,
           cst::textcolor);

  return;
}

// This is the extended version of the game CLiTBot. We will bring about much
// more features to the project. We will complete this later in this term.

#include "const.h"
#include "raylib-cpp.hpp"
#include "struct.h"

int main_ex() {
    // This is the entrance of the extended version of the game CLiTBot, and it
    // will be called in main.cpp.

    Ex_game *game = new Ex_game(cst::SAVE_PATH, cst::CMD_LIM);
    game->set_main_window(cst::SCREEN_WIDTH, cst::SCREEN_HEIGHT,
                          cst::PROJ_NAME);
    game->grid_init();
    // Here we genetats the backend game and the window interface.

    SetTargetFPS(cst::TARGET_FPS);

    while (game->is_running()) {

        game->ex_process();

        // MARK: Drawing process

        game->get_main_window()->BeginDrawing();

        game->get_main_window()->ClearBackground(RAYWHITE);

        game->draw_grid();

        game->draw_text();

        if (game->should_show_help()) {
            game->show_help_window();
            game->get_main_window()->EndDrawing();
            continue;
        } else if (game->should_show_start_window()) {
            game->show_start_window();
            game->get_main_window()->EndDrawing();
            continue;
        } else {
            game->show_game_view();
            game->get_main_window()->EndDrawing();
            continue;
        }

        game->get_main_window()->EndDrawing();
    }

    game->get_main_window()->Close();

    delete game;

    return 0;
}

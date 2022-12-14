// Here we store the constants used in our program.
#ifndef _CONSTS_IN_THE_GAME_
#define _CONSTS_IN_THE_GAME_

#include <string>

#include "raylib-cpp.hpp"
#include "struct.h"

// MARK: Constants

namespace cst {

const std::string PROJ_NAME = "CLiTBot!";

const int MAX_ROW = 100;

const int MAX_COL = 100;

const int MAX_LIGHTS = 15;

const int CMD_LIM = 50;

const std::string SAVE_PATH = "./output/";

// MARK: Used in Imgdraw

const int SCREEN_WIDTH = 900;

const int SCREEN_HEIGHT = 450;

const int WIDGET_WIDTH = 130;

const int TARGET_FPS = 60;

const pix grey_blue = {216, 170, 143};

const pix dark_grey = {132, 116, 107};

const pix light_grey = {230, 208, 195};

const pix background_color = {233, 233, 233};

const pix light_off = {123, 124, 221};

const pix light_on = {164, 225, 168};

const pix dark_line = {23, 23, 23};

const pix white_pix = {255, 255, 255};

const int cell_length = 100;

const int cell_width = 70;

const int cell_height = 30;

const int bot_width_pixels = 75;

const int bot_height_pixels = 150;

const int max_cells_l = 19;

const int max_cells_w = 14;

const std::string path_to_bot_up = "./resources/bot_up.bmp";

const std::string path_to_bot_down = "./resources/bot_down.bmp";

const std::string path_to_bot_right = "./resources/bot_right.bmp";

const std::string path_to_bot_left = "./resources/bot_left.bmp";

const BMPFileHeader BFH = {
    0x4D42, (SCREEN_WIDTH - WIDGET_WIDTH) * SCREEN_HEIGHT * 3 + 0x36, 0, 0,
    0x36};

const BMPInfoHeader BIH = {0x28,
                           SCREEN_WIDTH - WIDGET_WIDTH,
                           SCREEN_HEIGHT,
                           1,
                           24,
                           0,
                           (SCREEN_WIDTH - WIDGET_WIDTH) * SCREEN_HEIGHT,
                           {0}};

// MARK: Used in Ex_Imgdraw

const int image_count = 17;

const std::string img_path = "../resources/";

const raylib::Vector2 ver_line_0_pos(130.0f, 0.0f);

const raylib::Vector2 ver_line_0_size(2.0f, 450.0f);

const raylib::Vector2 ver_line_1_pos(100.0f, 0.0f);

const raylib::Vector2 ver_line_1_size(2.0f, 30.0f);

const raylib::Vector2 hor_line_0_pos(0.0f, 30.0f);

const raylib::Vector2 hor_line_0_size(130.0f, 2.0f);

const raylib::Vector2 hor_line_1_pos(0.0f, 330.0f);

const raylib::Vector2 hor_line_1_size(130.0f, 2.0f);

const raylib::Vector2 help_background_pos(102.0f, 0.0f);

const raylib::Vector2 help_background_size(26.0f, 28.0f);

const raylib::Vector2 game_view_pos(132.0f, 0.0f);

const raylib::Vector2 game_view_size(768.0f, 450.0f);

const raylib::Vector2 dynamic_cursor_start_pos(25.0f, 338.0f);

const raylib::Vector2 dynamic_cursor_size(2.0f, 18.0f);

const raylib::Vector2 text_space_pos(0.0f, 332.0f);

const raylib::Vector2 text_space_size(130.0f, 118.0f);

const raylib::Color rayblue(149, 177, 204);

const raylib::Color raylightblue(189, 208, 241);

const raylib::Color midgrey(237, 237, 237);

const raylib::Color textcolor(79, 101, 133);

const char start_message[] =
    "Press Space to select a map \n\t\t\t and start the game!";

const raylib::Vector2 message_start_pos(5.0f, 36.0f);

const raylib::Vector2 CMD_list_start_pos(7.0f, 52.0f);

const raylib::Vector2 cell_pos_delta_x(51.0f, -35.0f);

const raylib::Vector2 cell_pos_delta_y(51.0f, 35.0f);

const raylib::Vector2 cell_pos_delta_h(0.0f, -30.0f);

const raylib::Vector2 bot_pos_delta(27.5f, -60.0f);

const raylib::Vector2 center_float(-100.0f, -40.0f);

const raylib::Vector2 light_delta(46.0f, -183.0f);

const char reminder_message[] = "CMD-list:";

const char warning_message[] = "Unknown cmd!";

const std::string file_error_message = "发生了一些错误，文件没能正常打开？！";

const int message_max_len = 10;

const int CMD_list_max_len = 13;

const int char_height_18 = 20;

} // namespace cst

#endif

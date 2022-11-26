// Here we store the constants used in our program.
#ifndef _CONSTS_IN_THE_GAME_
#define _CONSTS_IN_THE_GAME_

#include <string>
#include "struct.h"

// MARK: Constants

namespace cst{

const int MAX_ROW = 100;

const int MAX_COL = 100;

const int MAX_LIGHTS = 15;

const int CMD_LIM = 50;

const std::string SAVE_PATH = "./output/";

// MARK: Used in Imgdraw

const int SCREEN_WIDTH = 900;

const int SCREEN_HEIGHT = 450;

const int WIDGET_WIDTH = 100;

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

const int max_cells_l = 20;

const int max_cells_w = 14;

const std::string path_to_bot_up = "./resources/bot_up.bmp";

const std::string path_to_bot_down = "./resources/bot_down.bmp";

const std::string path_to_bot_right = "./resources/bot_right.bmp";

const std::string path_to_bot_left = "./resources/bot_left.bmp";

const BMPFileHeader BFH = {0x4D42, (SCREEN_WIDTH - WIDGET_WIDTH) * SCREEN_HEIGHT * 3 + 0x36, 0, 0, 0x36};

const BMPInfoHeader BIH = {0x28, SCREEN_WIDTH - WIDGET_WIDTH, SCREEN_HEIGHT, 1, 24, 0, (SCREEN_WIDTH - WIDGET_WIDTH) * SCREEN_HEIGHT, {0}};
  
}

#endif

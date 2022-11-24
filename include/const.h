// Here we store the constants used in our program.
#ifndef _CONSTS_IN_THE_GAME_
#define _CONSTS_IN_THE_GAME_

#include <string>

// MARK: Related structures

struct BMPFileHeader{
    char id[2];
    unsigned int size;
    int res1;
    int res2;
    unsigned int offset;
};

struct BMPInfoHeader{
    int head_length;
    unsigned int pic_width;
    unsigned int pic_height;
    unsigned int surfaces;
    unsigned int depth;
    unsigned int archive_method;
    unsigned int pic_size;
    unsigned int res[4]; // These data will not be used in our program.
};

// MARK: Constants

namespace cst{

const int MAX_ROW = 100;

const int MAX_COL = 100;

const int MAX_LIGHTS = 15;

const int CMD_LIM = 50;

const std::string SAVE_PATH = "./output/";

const int SCREEN_WIDTH = 900;

const int SCREEN_HEIGHT = 450;

const int WIDGET_WIDTH = 100;

const int TARGET_FPS = 60;

const BMPFileHeader BFH = {{'B', 'M'}, (SCREEN_WIDTH - WIDGET_WIDTH) * SCREEN_HEIGHT * 3 + 0x36, 0, 0, 0x36};

const BMPInfoHeader BIH = {0x28, SCREEN_WIDTH - WIDGET_WIDTH, SCREEN_HEIGHT, 1, 24, 0, (SCREEN_WIDTH - WIDGET_WIDTH) * SCREEN_HEIGHT, {0}};
  
}

#endif

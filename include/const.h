// Here we store the constants used in our program.
#ifndef _CONSTS_IN_THE_GAME_
#define _CONSTS_IN_THE_GAME_

#include <string>

// MARK: Related structures

#pragma pack(1)
struct BMPFileHeader{
    short id;
    int size;
    short res1;
    short res2;
    int offset;
};

struct BMPInfoHeader{
    int head_length;
    int pic_width;
    int pic_height;
    short surfaces;
    short depth;
    int archive_method;
    int pic_size;
    int res[4]; // These data will not be used in our program.
};
#pragma pack()

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

const BMPFileHeader BFH = {0x4D42, (SCREEN_WIDTH - WIDGET_WIDTH) * SCREEN_HEIGHT * 3 + 0x36, 0, 0, 0x36};

const BMPInfoHeader BIH = {0x28, SCREEN_WIDTH - WIDGET_WIDTH, SCREEN_HEIGHT, 1, 24, 0, (SCREEN_WIDTH - WIDGET_WIDTH) * SCREEN_HEIGHT, {0}};
  
}

#endif

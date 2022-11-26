// Here we'll define the constructors of the classes defined in struct.h

#include "struct.h"


Game::Game(std::string path, int cmd_lim, Map * map, Bot * bot){
    m_map = map;
    m_bot = bot;
    m_path = path;
    m_cmd_lim = cmd_lim;
    m_running = true;
}

Map::Map(Cell * cells, Light * lights, int light_count, std::string name){
    m_cells = cells;
    m_lights = lights;
    m_light_count = light_count;
    m_name = name;
}

Bot::Bot(Position & pos, Direction dir){
    m_pos = pos;
    m_dir = dir;
}

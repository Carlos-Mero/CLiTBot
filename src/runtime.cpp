// This is the module that reads from the input and runs the whole game.

#include "const.h"
#include "struct.h"
#include <iostream>
#include <stdio.h>

// MARK: Standard features

void Bot::move() {
    // This function moves the bot.
    switch (m_dir) {
    case up:
        m_pos.y--;
        break;
    case left:
        m_pos.x--;
        break;
    case down:
        m_pos.y++;
        break;
    case right:
        m_pos.x++;
        break;

    default:
        break;
    }
    return;
}

void Bot::jump(Direction d) {

    switch (d) {
    case up:
        m_pos.h++;
        break;
    case down:
        m_pos.h--;
        break;

    default:
        break;
    }

    return;
}

void Bot::turn(Direction d) {
    // This function changes the direction of the bot.

    if (d == left) {
        switch (m_dir) {
        case up:
            m_dir = left;
            break;
        case left:
            m_dir = down;
            break;
        case down:
            m_dir = right;
            break;
        case right:
            m_dir = up;
            break;

        default:
            break;
        }
    } else if (d == right) {
        switch (m_dir) {
        case up:
            m_dir = right;
            break;
        case left:
            m_dir = up;
            break;
        case down:
            m_dir = left;
            break;
        case right:
            m_dir = down;
            break;

        default:
            break;
        }
    } else {
        std::cout << "发生了一些错误，无法处理转向方向" << std::endl;
    }

    return;
}

void Map::light_lit(Position pos) {
    // This function is called when the player uses the "LIT" command.
    // This will light the light at that position, and decreases the light_count
    // by 1.

    for (int i = 0; i < m_light_count; i++) {
        if (pos.x == m_lights[i].pos.x && pos.y == m_lights[i].pos.y &&
            !m_lights[i].turned_on) {
            m_lights[i].turned_on = true;
            goto Success;
        }
    }

    std::cout << "不行，这里没有需要点亮的灯……" << std::endl;
    return;

Success:

    m_light_remaining--;
    return;
}

void Game::set_map(std::string map_path) {
    // This method loads the map into the game class.
    // Use the "new" operator and construct a map object, then assign the
    // pointer to it to the variable m_map.

    std::ifstream map_file;
    map_file.open("../" + map_path);

    m_map = new Map();
    std::string temp_s;
    map_file >> temp_s;
    m_map->set_name(temp_s);
    // This is the first line in the map file.
    map_file >> m_map->m_row >> m_map->m_col >> m_map->m_cell_count >>
        m_map->m_light_count;
    map_file >> m_cmd_lim;
    // This is the second line.
    // We can lately write the map file using the input order here.

    m_map->m_light_remaining = m_map->m_light_count;

    Cell  *temp_cells  = new Cell[m_map->m_cell_count];
    Light *temp_lights = new Light[m_map->m_light_count];

    int temp  = 0;
    int count = 0;

    for (int i = 0; i < m_map->m_row * m_map->m_col; i++) {
        map_file >> temp;
        if (temp == 0) {
            continue;
        } else {
            temp_cells[count].pos.h = temp - 1;
            temp_cells[count].pos.y = i / m_map->m_col - m_map->m_row / 2;
            temp_cells[count].pos.x = i % m_map->m_col - m_map->m_col / 2;
            // Here the position of the bot can have a minus value, this refers
            // to the distance to the center of the view.
            count++;
        }
    }

    count = 0;
    for (int i = 0; i < m_map->m_light_count; i++) {
        map_file >> temp;
        temp_lights[count].pos.x = temp - m_map->m_col / 2;
        map_file >> temp;
        temp_lights[count].pos.y = temp - m_map->m_row / 2;
        count++;
    }

    m_map->set_cells(temp_cells);
    m_map->set_lights(temp_lights);

    map_file.close();

    return;
}

void Game::set_bot(std::string map_path) {
    // This will set a value of the variable m_bot, just like what the function
    // above does.

    std::ifstream map_file;
    map_file.open("../" + map_path);

    Position  temp_pos;
    Direction temp_dir;

    int  num;
    char buff[1024];

    map_file.getline(buff, sizeof(buff));
    map_file.getline(buff, sizeof(buff));

    for (int i = 0; i < m_map->m_row + m_map->m_light_count; i++) {
        map_file.getline(buff, sizeof(buff));
    }

    map_file >> temp_pos.x >> temp_pos.y >> temp_pos.h;
    temp_pos.h--;
    map_file >> num;

    switch (num) {
    case 0:
        temp_dir = up;
        break;
    case 1:
        temp_dir = left;
        break;
    case 2:
        temp_dir = down;
        break;
    case 3:
        temp_dir = right;
        break;

    default:
        break;
    }

    m_bot = new Bot(temp_pos, temp_dir);

    map_file.close();

    return;
}

void Game::process() {
    // This is the main function running behind the game loop.
    // It will need the cooperation of all three modules of the game.
    // In this function we may need to call many other methods of the class
    // Game. All variables in this game will be updated here in this method.

   if (m_cmd_lim != 0) {
        cin_cmd();
        run_command();
    } else if (m_cmd_lim == 0) {
        std::cout << "指令数已达到上限，游戏失败（悲" << std::endl;
        std::cout << "可以使用LOAD命令重新开始，或者按下control+C结束游戏"
                  << std::endl;
    }

    return;
}

void Game::run_command() {
    // This function handles the command inputed here.

    if (m_cmd == "LOAD") {
        std::cin >> m_cmd;
        // Here, m_cmd is temperarily uesd to store the path to the map.
        set_map(m_cmd);
        set_bot(m_cmd);
        std::cout << "地图已加载完毕！" << std::endl;
    } else if (m_cmd == "AUTOSAVE") {
        std::cin >> m_cmd;
        if (m_cmd == "ON") {
            m_auto_save_id = true;
        } else if (m_cmd == "OFF") {
            m_auto_save_id = false;
        } else {
            std::cout << "输入参数有误" << std::endl;
        }
    } else if (m_cmd == "LIMIT") {
        std::cin >> m_cmd_lim;
    } else if (m_cmd == "STATUS") {
        op_info();
    } else if (m_cmd == "OP") {
        // MARK: TODO
    } else if (m_cmd == "RUN") {
        // MARK: TODO
    } else if (m_cmd == "HELP") {
        show_help();
    } else if (m_cmd == "EXIT") {
        std::cout << "感谢您的游玩！" << std::endl;
        m_running = false;
    } else {
        std::cout << "很抱歉，我不太懂这个指令是什么意思……" << std::endl;
    }

    return;
}

// MARK: Extended features

void Ex_game::grid_init() {

    // MARK: Initializer of the game

    pics = new raylib::Image[cst::image_count];

    tx = new raylib::Texture[cst::image_count];

    m_font = GetFontDefault();

    pics[0] = raylib::Image(cst::img_path + "cell.png");

    pics[1] = raylib::Image(cst::img_path + "light.png");

    pics[2] = raylib::Image(cst::img_path + "light_lit.png");

    pics[3] = raylib::Image(cst::img_path + "bot_up_stand.png");

    pics[4] = raylib::Image(cst::img_path + "bot_up_walk_1.png");

    pics[5] = raylib::Image(cst::img_path + "bot_up_walk_2.png");

    pics[6] = raylib::Image(cst::img_path + "bot_left_stand.png");

    pics[7] = raylib::Image(cst::img_path + "bot_left_walk_1.png");

    pics[8] = raylib::Image(cst::img_path + "bot_left_walk_2.png");

    pics[9] = raylib::Image(cst::img_path + "bot_down_stand.png");

    pics[10] = raylib::Image(cst::img_path + "bot_down_walk_1.png");

    pics[11] = raylib::Image(cst::img_path + "bot_down_walk_2.png");

    pics[12] = raylib::Image(cst::img_path + "bot_right_stand.png");

    pics[13] = raylib::Image(cst::img_path + "bot_right_walk_1.png");

    pics[14] = raylib::Image(cst::img_path + "bot_right_walk_2.png");

    pics[15] = raylib::Image(cst::img_path + "bot_lit_1.png");

    pics[16] = raylib::Image(cst::img_path + "bot_lit_2.png");

    for (int i = 0; i < cst::image_count; i++) {
        pics[i].Format(PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        tx[i] = pics[i].LoadTexture();
    }

    delete[] pics;
    // This loads the images used in the game, and convert them for GPU to
    // process.

    help_stream = new std::ifstream;

    help_stream->open("../maps/help.txt", std::ios::in);

    if (!help_stream->is_open()) {
        std::cout << cst::file_error_message << std::endl;
        m_running = false;
        return;
    }

    std::string temp_str;
    char        buf[1024];

    temp_str = "";

    while (help_stream->getline(buf, sizeof(buf))) {
        temp_str += (std::string)buf;
        temp_str += "\n";
    }

    help_text = new raylib::Text(m_font, temp_str, 17.0f, 1.0f, cst::textcolor);

    help_stream->close();

    delete help_stream;

    ver_line_0 =
        new raylib::Rectangle(cst::ver_line_0_pos, cst::ver_line_0_size);

    ver_line_1 =
        new raylib::Rectangle(cst::ver_line_1_pos, cst::ver_line_1_size);

    hor_line_0 =
        new raylib::Rectangle(cst::hor_line_0_pos, cst::hor_line_0_size);

    hor_line_1 =
        new raylib::Rectangle(cst::hor_line_1_pos, cst::hor_line_1_size);

    game_space = new raylib::Rectangle(cst::game_view_pos, cst::game_view_size);

    text_space =
        new raylib::Rectangle(cst::text_space_pos, cst::text_space_size);

    dynamic_curser = new raylib::Rectangle(cst::dynamic_cursor_start_pos,
                                           cst::dynamic_cursor_size);

    help_background = new raylib::Rectangle(cst::help_background_pos,
                                            cst::help_background_size);

    help_text_color = RAYWHITE;

    help_background_color = cst::rayblue;

    help_index = 0;

    start_index = true;

    frame_count = 0;

    text_selected = 1;

    input_chars[10] = '\0';

    input_count = 0;

    command_list_index = 0;

    return;
}

// MARK: Input handler

void Ex_game::input_process() {

    int key = GetCharPressed();

    while (key > 0) {

        if ((key >= 32) && (key <= 125) && (key != KEY_SPACE) &&
            (input_count < cst::message_max_len)) {

            input_chars[input_count] = (char)key;
            input_count++;
            input_chars[input_count] = '\0';
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && input_count > 0) {

        input_count--;
        input_chars[input_count] = '\0';

    } else if (IsKeyPressed(KEY_BACKSPACE) && input_count == 0) {

        input_chars[input_count] = '\0';

    } else if (IsKeyPressed(KEY_ENTER) && input_count > 0) {

        strcpy(command_lists[command_list_index % cst::CMD_list_max_len],
               input_chars);
        command_list_index++;
        input_count              = 0;
        input_chars[input_count] = '\0';
    }

    dynamic_curser->SetPosition(cst::dynamic_cursor_start_pos.GetX() +
                                    MeasureText(input_chars, 18),
                                dynamic_curser->GetY());

    return;
}

// MARK: Ex_process workflow

void Ex_game::ex_process() {

    if (main_window->ShouldClose()) {
        m_running = false;
    }

    mouse_pos = raylib::Mouse::GetPosition();

    if (help_background->CheckCollision(mouse_pos)) {
        help_background_color = cst::raylightblue;
        if (raylib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
            help_index++;
        }
    } else {
        help_background_color = cst::rayblue;
    }

    if (IsKeyPressed(KEY_SPACE)) {
        start_index = false;
        map_selection();
        help_index = 0;
    }

    if (text_space->CheckCollision(mouse_pos) &&
        raylib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
        text_selected = true;
    }

    if (!text_space->CheckCollision(mouse_pos) &&
        raylib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
        text_selected = false;
    }

    if (frame_count / 32 % 2 && text_selected) {
        dynamic_curser->Draw(cst::rayblue);
    }

    if (text_selected) {
        input_process();
    }

    frame_count++;

    return;
}

// MARK: Map_selection_process

void Ex_game::map_selection() { return; }

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
    map_file.open(map_path);
    
    if (!map_file.is_open()) {
        std::cout << "地图载入失败……请检查路径输入是否正确" << std::endl;
        return;
    }
    
    int temp = 0;
    int count = 0;

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
    
    map_file >> proc_available;
    
    for (int i = 0; i < proc_available; i++) {
        map_file >> proc_lim[i];
    }

    m_map->m_light_remaining = m_map->m_light_count;

    Cell  *temp_cells  = new Cell[m_map->m_cell_count];
    Light *temp_lights = new Light[m_map->m_light_count];

    int *temps = new int[m_map->m_col];

    for (int i = 0; i < m_map->m_row; i++) {
        for (int j = 0; j < m_map->m_col; j++) {
            map_file >> temps[j];
        }
        for (int j = m_map->m_col-1; j >= 0; j--) {
            temp = -1;
            while (temp < temps[j] - 1) {
                temp++;
                temp_cells[count].pos.h = temp;
                temp_cells[count].pos.y = i - m_map->m_row / 2 + 1;
                temp_cells[count].pos.x = j - m_map->m_col / 2 + 1;
                // Here the position of the bot can have a minus value, this refers
                // to the distance to the center of the view.
                count++;
            }
        }
    }
    
    delete[] temps;

    count = 0;
    for (int i = 0; i < m_map->m_light_count; i++) {
        map_file >> temp;
        temp_lights[count].pos.x = temp - m_map->m_col / 2 + 1;
        map_file >> temp;
        temp_lights[count].pos.y = temp - m_map->m_row / 2 + 1;
        map_file >> temp;
        temp_lights[count].pos.h = temp - 1;
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
    map_file.open(map_path);
    
    if (!map_file.is_open()) {
        std::cout << "地图载入失败……请检查路径输入是否正确" << std::endl;
        return;
    }

    Position  temp_pos;
    Direction temp_dir;

    int  num;
    char buff[1024];

    map_file.getline(buff, sizeof(buff));
    map_file.getline(buff, sizeof(buff));
    map_file.getline(buff, sizeof(buff));

    for (int i = 0; i < m_map->m_row + m_map->m_light_count; i++) {
        map_file.getline(buff, sizeof(buff));
    }

    map_file >> temp_pos.x >> temp_pos.y >> temp_pos.h;
    temp_pos.x -= m_map->m_col / 2;
    temp_pos.y -= m_map->m_row / 2;
    temp_pos.x++;
    temp_pos.y++;
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
        std::cout << "可以使用LOAD命令重新开始，或者使用EXIT命令结束游戏"
                  << std::endl;
    }
    
    if (m_map->m_light_remaining == 0) {
        std::cout << "恭喜你打败了ETO🎉，拯救了地球文明！" << std::endl;
        std::cout << "可以使用LOAD命令重新开始，或者使用EXIT命令结束游戏"
                  << std::endl;
        m_map->m_light_remaining--;
    }

    return;
}

void Game::run(std::string cmd) {
    
    if (m_cmd_lim <= 0) {
        return;
    }
    
    if (m_auto_save_id > 0) {
        auto_op_map();
    }
    
    m_cmd_lim--;
    
    bool success_index = false;
    
    if (cmd == "TL") {
        m_bot->turn(left);
    }else if (cmd == "TR") {
        m_bot->turn(right);
    }else if (cmd == "LIT") {
        m_map->light_lit(m_bot->current_position());
    }else if (cmd == "MOV") {
        
        m_bot->move();
        
        for (int i = m_map->m_cell_count - 1; i >= 0; i--) {
            if (m_map->cells()[i].pos.x == m_bot->current_position().x && m_map->cells()[i].pos.y == m_bot->current_position().y && m_map->cells()[i].pos.h == m_bot->current_position().h) {
                m_bot->move();
                success_index = true;
                break;
            }else {
                continue;
            }
        }
        
        m_bot->turn(left);
        m_bot->turn(left);
        m_bot->move();
        m_bot->turn(left);
        m_bot->turn(left);
        
        if (!success_index) {
            std::cout << "警告⚠️，不能朝着这个方向移动。" << std::endl;
        }
        
    }else if (cmd == "JMP") {
        
        m_bot->move();
        
        for (int i = m_map->m_cell_count - 1; i >= 0; i--) {
            if (m_map->cells()[i].pos.x == m_bot->current_position().x && m_map->cells()[i].pos.y == m_bot->current_position().y && (m_map->cells()[i].pos.h == m_bot->current_position().h + 1 || m_map->cells()[i].pos.h == m_bot->current_position().h - 1)) {
                m_bot->set_position(m_map->cells()[i].pos);
                m_bot->move();
                success_index = true;
                break;
            }else {
                continue;
            }
        }
        
        m_bot->turn(left);
        m_bot->turn(left);
        m_bot->move();
        m_bot->turn(left);
        m_bot->turn(left);
        
        if (!success_index) {
            std::cout << "警告⚠️，不能朝着这个方向跳。" << std::endl;
        }
        
    }else if (cmd[0] == 'P') {
        int n = int(cmd[1]) - 48;
        
        for (int i = 0; i < proc_length[n]; i++) {
            run(proc_content[n][i]);
        }
    }else if (cmd == "MAIN") {
        for (int i = 0; i < proc_length[0]; i++) {
            run(proc_content[0][i]);
        }
    }else {
        std::cout << "发生了一些意外！有不明指令输入。" << std::endl;
    }
    
    return;
}

void Game::open_proc() {
    
    std::cin >> m_cmd;
    
    std::ofstream proc_file;
    proc_file.open("../" + m_cmd, std::ios::out);
    
    if (!proc_file.is_open()) {
        std::cout << "文件没成功打开，寄！" << std::endl;
        return;
    }
    
    int proc_num;
    int proc_nums[10];
    std::string current_cmd;
    
    std::cin >> proc_num;
    
    proc_file << proc_num << "\n";
    
    for (int i = 0; i < proc_num; i++) {
        std::cin >> proc_nums[i];
        if (proc_nums[i] > proc_lim[i]) {
            std::cout << "指令数超出上限，请再做考虑。" << std::endl;
            return;
        }
        proc_file << proc_nums[i] << " ";
        for (int j = 0; j < proc_nums[i]; j++) {
            std::cin >> current_cmd;
            proc_file << current_cmd << " ";
        }
        proc_file << "\n";
    }
    
    proc_file.close();
    
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
    
    select_index = true;

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
        m_cmd = command_lists[command_list_index % cst::CMD_list_max_len];
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

Position operator + (Position a, Position b) {
    Position te;
    te.x = a.x + b.x;
    te.y = a.y + b.y;
    te.h = a.h + b.h;
    return te;
}

bool operator == (Position a, Position b) {
    return (a.x == b.x && a.y == b.y && a.h == b.h);
}

void Ex_game::ex_process() {

    if (main_window->ShouldClose()) {
        m_running = false;
    }
    
    if (select_index) {
        if (IsFileDropped()) {
            map_file_path = LoadDroppedFiles();
            if (map_file_path.count != 0) {
                std::cout << map_file_path.count << std::endl;
                std::cout << map_file_path.paths[map_file_path.count-1] << std::endl;
                
                set_map(map_file_path.paths[map_file_path.count-1]);
                set_bot(map_file_path.paths[map_file_path.count-1]);
                
                start_index = false;
                select_index = false;
                
                UnloadDroppedFiles(map_file_path);
            }
        }
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
        start_index = true;
        select_index = true;
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
    
    if (m_cmd != "") {
        /*if (m_cmd == "TL") {
            m_bot->turn(left);
        }else if (m_cmd == "TR") {
            m_bot->turn(right);
        }else if (m_cmd == "MOV") {
            
            Position tmp;
            
            switch (m_bot->current_direction()) {
                case up:
                    tmp.y = -1;
                    break;
                case left:
                    tmp.x = -1;
                    break;
                case down:
                    tmp.y = 1;
                    break;
                case right:
                    tmp.x = 1;
                    break;
                    
                default:
                    break;
            }
            
            tmp = tmp + m_bot->current_position();
            
            for (int i = 0; i < m_map->m_cell_count; i++) {
                if (m_map->cells()[i].pos == tmp) {
                    moving_index = 1;
                }else {
                    continue;
                }
            }
            
        } else {
            std::cout << "无效指令，请检查……" << std::endl;
        }*/
        run(m_cmd);
        m_cmd = "";
    }

    frame_count++;

    return;
}

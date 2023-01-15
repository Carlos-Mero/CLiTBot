// This is the module that interacts with the user.

#include "const.h"
#include "struct.h"
#include <fstream>
#include <iostream>

// MARK: Standard features

void Game::cin_cmd() {
    // This function handles the interaction with the player.
    // It recieves the command and send it to the process method.
    std::cout << "请输入下一步指令" << std::endl;
    std::cin >> m_cmd;

    return;
}

void Game::show_help() {

    char         buff[1024];
    std::fstream text;
    
    std::cout << std::endl;
    
    for (int i = 0; i < 11; i++) {
        std::cout << "---";
    }
    std::cout << std::endl;
    text.open("../maps/help_cli.txt");

    while (text.getline(buff, sizeof(buff))) {
        std::cout << buff << std::endl;
    }
    
    for (int i = 0; i < 11; i++) {
        std::cout << "---";
    }
    std::cout << std::endl << std::endl;
    text.close();

    return;
}

void Game::op_info() {
    // This function handles the output of the information due to the command
    // sent in.
    
    std::cout << "Map Name: " << m_map->get_name() << std::endl
              << "Autosave ID: " << m_auto_save_id << std::endl
              << "Remaining steps: " << m_cmd_lim << std::endl;
    
    int *map_cli = new int[m_map->m_col * m_map->m_row];
    
    for (int i = 0; i < m_map->m_cell_count; i++) {
        map_cli[(m_map->cells()[i].pos.x - 1 + m_map->m_col / 2) + (m_map->cells()[i].pos.y - 1 + m_map->m_row / 2) * m_map->m_col] = m_map->cells()[i].pos.h + 1;
    }
    
    for (int i = 0; i < m_map->m_light_count; i++) {
        map_cli[(m_map->lights()[i].pos.x - 1 + m_map->m_col / 2) + (m_map->lights()[i].pos.y - 1 + m_map->m_row / 2) * m_map->m_col] += (100 + int(m_map->lights()[i].turned_on) * 1000);
    }
    
    map_cli[(m_bot->current_position().x - 1 + m_map->m_col / 2) + (m_bot->current_position().y - 1 + m_map->m_row / 2) * m_map->m_col] += 10000;
    
    std::string output_str;
    
    for (int i = 0; i < m_map->m_row; i++) {
        for (int j = 0; j < m_map->m_col; j++) {
            if (map_cli[j + i * m_map->m_col] % 100 == 0) {
                std::cout << "  ";
                continue;
            }
            output_str = "\e[";
            if (map_cli[j + i * m_map->m_col] / 10000 == 1) {
                output_str += "91;";
            }else {
                output_str += "92;";
            }
            
            if ((map_cli[j + i * m_map->m_col] / 100) % 10 == 1) {
                if ((map_cli[j + i * m_map->m_col] / 1000) % 10 == 1) {
                    output_str += "103;";
                }else {
                    output_str += "104;";
                }
            }else {
                output_str += "100;";
            }
            output_str += "1m";
            output_str += std::to_string(map_cli[j + i * m_map->m_col] % 100);
            std::cout << output_str << "\e[0m ";
        }
        std::cout << std::endl;
    }
    
    delete[] map_cli;
    
    std::cout << "Robot is facing ";
    
    switch (m_bot->current_direction()) {
        case up:
            std::cout << "up.";
            break;
        case left:
            std::cout << "left.";
            break;
        case down:
            std::cout << "down.";
            break;
        case right:
            std::cout << "right.";
            break;
            
        default:
            break;
    }
    
    std::cout << std::endl;
    
    std::cout << "Proc Limit: [";
    
    for (int i = 0; i < proc_available; i++) {
        std::cout << " " << proc_lim[i];
    }
    
    std::cout << " ]" << std::endl;

    return;
}

void Game::run_command() {
    // This function handles the command inputed here.

    if (m_cmd == "LOAD") {
        std::cin >> m_cmd;
        m_cmd = "../" + m_cmd;
        // Here, m_cmd is temperarily uesd to store the path to the map.
        set_map(m_cmd);
        set_bot(m_cmd);
        if (m_map != NULL) {
            std::cout << "地图已加载完毕！" << std::endl;
        }
    } else if (m_cmd == "AUTOSAVE") {
        std::cin >> m_cmd;
        if (m_cmd == "ON") {
            m_auto_save_id = 1;
            std::cout << "自动存储已启动。" << std::endl;
        } else if (m_cmd == "OFF") {
            m_auto_save_id = 0;
            std::cout << "自动存储已关闭。" << std::endl;
        } else {
            std::cout << "输入参数有误……不知道怎么办了" << std::endl;
        }
    } else if (m_cmd == "LIMIT") {
        std::cin >> m_cmd_lim;
    } else if (m_cmd == "STATUS") {
        op_info();
    } else if (m_cmd == "OP") {
        open_proc();
    } else if (m_cmd == "RUN") {
        
        std::cin >> m_cmd;
        std::ifstream proc_file;
        
        proc_file.open("../" + m_cmd);
        if (!proc_file.is_open()) {
            std::cout << "文件没成功打开，寄！" << std::endl;
            return;
        }
        int proc_num;
        proc_file >> proc_num;
        
        for (int i = 0; i < proc_num; i++) {
            proc_file >> proc_length[i];
            for (int j = 0; j < proc_length[i]; j++) {
                proc_file >> proc_content[i][j];
            }
        }
        
        proc_file.close();
        
        run("MAIN");
        
    } else if (m_cmd == "HELP") {
        show_help();
    } else if (m_cmd == "EXIT") {
        std::cout << "感谢您的游玩！" << std::endl;
        m_running = false;
    } else if (m_cmd == "SAVE") {
        op_map();
    } else {
        std::cout << "很抱歉，我不太懂这个指令是什么意思……" << std::endl;
    }
    
    if (m_auto_save_id > 0) {
        auto_op_map();
    }

    return;
}


// MARK: Extended features

void Ex_game::show_help_window() {

    help_text->Draw(cst::game_view_pos.GetX() + 8.0f,
                    cst::game_view_pos.GetY() + 5.0f);

    return;
}

void Ex_game::show_start_window() {

    DrawText(TextSubtext(cst::start_message, 0, frame_count / 4), 300, 180, 26,
             cst::textcolor);

    return;
}

// MARK: Map_selection_process

void Ex_game::map_selection() {
    
    start_index = false;
    select_index = false;
    return;
}

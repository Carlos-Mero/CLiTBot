// this is the module that draws and outputs the map of the game.

#include "const.h"
#include "struct.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

// MARK: Standard features

bool operator>(Position a, Position b) {
    return (a.h > b.h && a.y > b.y && a.x < b.x);
}
// a > b means that b is behind a.

void Game::op_cell(pix **main_map, Position cell_pos) {

    const int plt_center_x = (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH) / 2;
    const int plt_center_y = cst::SCREEN_HEIGHT / 2;

    int pltx =
        plt_center_x + (cst::cell_length / 2) * (cell_pos.x + cell_pos.y);

    int plty = plt_center_y +
               (cst::cell_width / 2) * (cell_pos.x - cell_pos.y) +
               cst::cell_height * cell_pos.h;

    for (int i = 0; i <= cst::cell_width / 2; i++) {
        for (int j = -(i * cst::cell_length) / cst::cell_width;
             j <= (i * cst::cell_length) / cst::cell_width; j++) {
            main_map[plty - i][pltx + j]                   = cst::light_grey;
            main_map[plty + i - cst::cell_width][pltx + j] = cst::light_grey;
        }
    }

    for (int i = -cst::cell_length / 2; i <= cst::cell_length / 2; i++) {
        int stp =
            cst::cell_width - (abs(i) * cst::cell_width) / cst::cell_length;
        for (int j = stp; j <= cst::cell_height + stp; j++) {
            main_map[plty - j][pltx + i] = cst::dark_grey;
        }
    }

    return;
}

void Game::op_light(pix **main_map, Position cell_pos) {
    const int plt_center_x = (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH) / 2;
    const int plt_center_y = cst::SCREEN_HEIGHT / 2;

    int pltx =
        plt_center_x + (cst::cell_length / 2) * (cell_pos.x + cell_pos.y);

    int plty = plt_center_y +
               (cst::cell_width / 2) * (cell_pos.x - cell_pos.y) +
               cst::cell_height * cell_pos.h;

    for (int i = 0; i <= cst::cell_width / 2; i++) {
        for (int j = -(i * cst::cell_length) / cst::cell_width;
             j <= (i * cst::cell_length) / cst::cell_width; j++) {
            main_map[plty - i][pltx + j]                   = cst::grey_blue;
            main_map[plty + i - cst::cell_width][pltx + j] = cst::grey_blue;
        }
    }
    return;
}

void Game::op_bot(pix **main_map, Position bot_pos, std::ifstream &bot_img) {

    const int plt_center_x = (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH) / 2;
    const int plt_center_y = cst::SCREEN_HEIGHT / 2;

    int pltx = plt_center_x + (cst::cell_length / 2) * (bot_pos.x + bot_pos.y);

    int plty = plt_center_y + (cst::cell_width / 2) * (bot_pos.x - bot_pos.y) +
               cst::cell_height * bot_pos.h + cst::bot_height_pixels -
               cst::cell_width / 2 - 10;

    bot_img.seekg(54L, std::ios::cur);

    pix *temp = new pix;

    for (int j = 0; j < cst::bot_height_pixels; j++) {
        for (int i = -cst::bot_width_pixels / 2; i <= cst::bot_width_pixels / 2;
             i++) {
            bot_img.read((char *)temp, sizeof(pix));
            if (temp->red + temp->green + temp->blue == 0) {
                continue;
            } else if (plty + j - cst::bot_height_pixels >=
                       cst::SCREEN_HEIGHT) {
                continue;
            } else {
                main_map[plty + j - cst::bot_height_pixels][pltx + i] = *temp;
            }
        }
        bot_img.seekg(3L, std::ios::cur);
    }

    delete temp;

    return;
}

void Game::op_map(std::string file_name) {
    // This function draws and saves the map of the game.
    std::ofstream mapfile;
    mapfile.open(cst::SAVE_PATH + file_name, std::ios::binary);
    // Warning! This method will open the file and wipe all the content existing
    // there! But for our purpose of saving the map, it's just fine.

    std::ifstream bot_img;
    switch (m_bot->current_direction()) {
    case up:
        bot_img.open(cst::path_to_bot_up, std::ios::binary);
        break;
    case down:
        bot_img.open(cst::path_to_bot_down, std::ios::binary);
        break;
    case right:
        bot_img.open(cst::path_to_bot_right, std::ios::binary);
        break;
    case left:
        bot_img.open(cst::path_to_bot_left, std::ios::binary);
        break;

    default:
        break;
    }

    if (!mapfile.is_open() || !bot_img.is_open()) {
        mapfile.close();
        bot_img.close();
        std::cout << cst::file_error_message << std::endl;
        return;
    }

    mapfile.write((char *)&cst::BFH, sizeof(cst::BFH));
    mapfile.write((char *)&cst::BIH, sizeof(cst::BIH));
    // Here we write in the header of the picture.

    pix **pic = new pix *[cst::SCREEN_HEIGHT];
    for (int i = 0; i < cst::SCREEN_HEIGHT; i++) {
        pic[i] = new pix[cst::SCREEN_WIDTH - cst::WIDGET_WIDTH];
        for (int j = 0; j < cst::SCREEN_WIDTH - cst::WIDGET_WIDTH; j++) {
            pic[i][j] = cst::background_color;
        }
    }

    for (int i = 0; i < m_map->m_cell_count; i++) {
        if (m_map->cells()[i].pos > m_bot->current_position()) {
            continue;
        }
        op_cell(pic, m_map->cells()[i].pos);
    }

    for (int i = 0; i < m_map->m_light_count; i++) {
        if (m_map->lights()[i].turned_on) {
            continue;
        }
        if (m_map->lights()[i].pos > m_bot->current_position()) {
            continue;
        }
        op_light(pic, m_map->lights()[i].pos);
    }

    op_bot(pic, m_bot->current_position(), bot_img);

    for (int i = 0; i < m_map->m_cell_count; i++) {
        if (!(m_map->cells()[i].pos > m_bot->current_position())) {
            continue;
        }
        op_cell(pic, m_map->cells()[i].pos);
    }

    for (int i = 0; i < m_map->m_light_count; i++) {
        if (m_map->lights()[i].turned_on) {
            continue;
        }
        if (!(m_map->lights()[i].pos > m_bot->current_position())) {
            continue;
        }
        op_light(pic, m_map->lights()[i].pos);
    }

    // This initializes the picture in the main memory.
    /*
        for (int i = 0; i < m_map->cells_count(); i++) {
            Position paint_pos = m_map->cells()[i].pos;

            // Get the relative position of the cells.
            paint_pos.x = paint_pos.x + paint_pos.y;
            paint_pos.y = paint_pos.x - paint_pos.y * 2;
            // Transfers the position of the cell to a 2.5D view.

            if (paint_pos.x >= -cst::max_cells_l / 2 &&
                paint_pos.x <= cst::max_cells_l / 2 &&
                paint_pos.y >= -cst::max_cells_w / 2 &&
                paint_pos.y <= cst::max_cells_w / 2) {
                int paint_center_l = paint_pos.x * cst::cell_length / 2 +
                                     (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH) /
       2;

                for (int x = paint_center_l - cst::cell_length / 2;
                     x <= paint_center_l + cst::cell_length / 2; x++) {

                    if (x < 0 || x > cst::SCREEN_WIDTH - cst::WIDGET_WIDTH) {
                        continue;
                    } else {
                        int paint_center_w = paint_pos.y * cst::cell_width / 2 +
                                             cst::SCREEN_HEIGHT / 2 +
                                             paint_pos.h * cst::cell_height;
                        int paint_width_expansion =
                            (70 - std::abs(x - paint_center_l) * 7 / 10) / 2;

                        for (int y = paint_center_w + paint_width_expansion + 1;
                             y <= paint_center_w - paint_width_expansion - 1;
       y--) {

                            if (y < 0 || y > cst::SCREEN_HEIGHT) {
                                continue;
                            } else {
                                pic[x][y] = cst::grey_blue;
                            }
                        }

                        for (int k = 0; k < paint_pos.h; k++) {

                            for (int y = paint_center_w - paint_width_expansion
       - k * cst::cell_height - 1; y >= paint_center_w - paint_width_expansion -
                                          (k + 1) * cst::cell_height;
                                 y--) {

                                if (y < 0 || y > cst::SCREEN_HEIGHT) {
                                    continue;
                                } else {
                                    if (x < paint_center_l &&
                                        paint_width_expansion != 0) {
                                        pic[x][y] = cst::grey_blue;
                                    } else if (x > paint_center_l &&
                                               paint_width_expansion != 0) {
                                        pic[x][y] = cst::dark_grey;
                                    } else {
                                        pic[x][y] = cst::dark_line;
                                    }
                                }
                            }
                        }
                        pic[x][paint_center_w + paint_width_expansion] =
                            cst::dark_line;
                        pic[x][paint_center_w - paint_width_expansion] =
                            cst::dark_line;
                    }
                }
            } else {
                continue;
            }
        }
        // This will draw the map to the main memory.
        // Then we will draw the bot on the center of the map.
        pix current_pixel;
        for (int x =
                 (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH - cst::bot_width_pixels)
       / 2; x <= (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH + cst::bot_width_pixels)
       / 2 && !bot_img.eof(); x++) { for (int y = (cst::SCREEN_HEIGHT +
       cst::bot_height_pixels) / 2; y >= (cst::SCREEN_HEIGHT -
       cst::bot_height_pixels) / 2 && !bot_img.eof(); y--) { bot_img.read((char
       *)&current_pixel, sizeof(pix)); if (current_pixel.green ==
       cst::white_pix.green && current_pixel.blue == cst::white_pix.blue &&
                    current_pixel.red == cst::white_pix.red) {
                    continue;
                } else {
                    pic[x][y] = current_pixel;
                }
            }
        }

        //*/

    for (int x = 0; x < cst::SCREEN_HEIGHT; x++) {
        mapfile.write((char *)pic[x],
                      (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH) * sizeof(pix));
        mapfile.seekp(2L, std::ios::cur);
    }
    // This draws the picture to the file.

    mapfile.close();
    bot_img.close();
    for (int i = 0; i < cst::SCREEN_HEIGHT; i++) {
        delete[] pic[i];
    }
    delete[] pic;
    // release the memory occupied by the pointer.

    std::cout << "当前地图已输出！" << std::endl;

    return;
}

void Game::auto_op_map() {
    // This function automatically saves and outputs the condition of the map.
    if (m_auto_save_id) {
        op_map(std::to_string(m_auto_save_id) + ".bmp");
    }

    m_auto_save_id++;

    return;
}

// MARK: Extended features

void Ex_game::set_main_window(int width, int height, std::string title) {

    if (main_window != NULL) {
        delete main_window;
    }

    main_window = new raylib::Window(width, height, title);
}

void Ex_game::draw_grid() {

    ver_line_0->Draw(cst::rayblue);

    ver_line_1->Draw(cst::rayblue);

    hor_line_0->Draw(cst::rayblue);

    hor_line_1->Draw(cst::rayblue);

    game_space->Draw(cst::midgrey);

    help_background->Draw(help_background_color);

    return;
}

void Ex_game::draw_text() {

    DrawText("GLiTBot!", 10, 7, 20, cst::textcolor);

    DrawText("?", 108, 6, 20, help_text_color);

    DrawText(cst::reminder_message, cst::message_start_pos.GetX(),
             cst::message_start_pos.GetY(), 18, cst::textcolor);

    DrawText(">", cst::dynamic_cursor_start_pos.GetX() - 15.0f,
             cst::dynamic_cursor_start_pos.GetY(), 18, cst::textcolor);

    DrawText(TextFormat(input_chars, input_count, cst::message_max_len),
             cst::dynamic_cursor_start_pos.GetX(),
             cst::dynamic_cursor_start_pos.GetY(), 18, cst::textcolor);

    for (int i = 0; i < cst::CMD_list_max_len; i++) {

        DrawText(TextFormat("%02i.", i), 6.0f,
                 cst::message_start_pos.GetY() + (i + 1) * cst::char_height_18,
                 14,
                 (i == (command_list_index % cst::CMD_list_max_len))
                     ? cst::textcolor
                     : cst::raylightblue);

        DrawText(command_lists[i], 26.0f,
                 cst::message_start_pos.GetY() + (i + 1) * cst::char_height_18,
                 18,
                 (i + 1 == (command_list_index % cst::CMD_list_max_len))
                     ? cst::textcolor
                     : cst::raylightblue);
    }

    return;
}

void Ex_game::show_game_view() {

    raylib::Vector2 plt_center =
        cst::game_view_pos + cst::game_view_size / 2 + cst::center_float;

    for (int i = 0; i < m_map->cells_count(); i++) {
        if (m_map->cells()[i].pos > m_bot->current_position()) {
            continue;
        }
        tx[cell].Draw(plt_center +
                      cst::cell_pos_delta_x * m_map->cells()[i].pos.x +
                      cst::cell_pos_delta_y * m_map->cells()[i].pos.y +
                      cst::cell_pos_delta_h * m_map->cells()[i].pos.h);
    }
    // This draws the cells below the bot.

    // We will then draw the light to the map, depending on their lit_id
    for (int i = 0; i < m_map->light_count(); i++) {
        if (!(m_map->lights()[i].pos > m_bot->current_position())) {
            continue;
        }
        if (m_map->lights()[i].turned_on) {
            tx[light_lit].Draw(
                plt_center + cst::cell_pos_delta_x * m_map->lights()[i].pos.x +
                cst::cell_pos_delta_y * m_map->lights()[i].pos.y +
                cst::light_delta);
        } else {
            tx[light].Draw(plt_center +
                           cst::cell_pos_delta_x * m_map->lights()[i].pos.x +
                           cst::cell_pos_delta_y * m_map->lights()[i].pos.y +
                           cst::light_delta);
        }
    }

    int bot_status;

    raylib::Vector2 bot_pos_delta = cst::bot_pos_delta;

    // Here we choose the texture due to the status of the bot.

    switch (m_bot->current_direction()) {
    case up:
        bot_status = 3;
        break;
    case left:
        bot_status = 6;
        break;
    case down:
        bot_status = 9;
        break;
    case right:
        bot_status = 12;
        break;

    default:
        break;
    }

    // This handles moving process
    if (moving_index > 0) {
        moving_index++;
        moving_index %= 33;
        bot_status = bot_status + (moving_index / 16 + 1) % 3;
        switch (m_bot->current_direction()) {
        case up:
            bot_pos_delta = bot_pos_delta - cst::cell_pos_delta_y *
                                                ((float)moving_index / 33.0f);
            break;
        case down:
            bot_pos_delta = bot_pos_delta + cst::cell_pos_delta_y *
                                                ((float)moving_index / 33.0f);
            break;

        case left:
            bot_pos_delta = bot_pos_delta - cst::cell_pos_delta_x *
                                                ((float)moving_index / 33.0f);
            break;
        case right:
            bot_pos_delta = bot_pos_delta + cst::cell_pos_delta_x *
                                                ((float)moving_index / 33.0f);
            break;

        default:
            break;
        }
        if (moving_index == 32) {
            m_bot->move();
        }
    }

    // This handles the jumping process
    if (jumping_index != 0) {
        // Here we declare that jumping_index > 0 means that the bot is jumping
        // up, and minus value means jumping down.
        moving_index = 1;
        // This will recall the process before, and handle the horizenal move of
        // the bot.
        if (jumping_index < 0) {
            jumping_index++;
            jumping_index %= 33;
            bot_pos_delta += cst::cell_pos_delta_h *
                             (1 - pow(jumping_index + 13.669f, 2) / 186.84286);
        } else {
            jumping_index--;
            jumping_index %= 33;
            bot_pos_delta +=
                cst::cell_pos_delta_h *
                (2 - pow(jumping_index - 19.33095f, 2) / 373.68572f);
        }

        if (jumping_index == 32) {
            m_bot->jump(up);
        } else if (jumping_index == -32) {
            m_bot->jump(down);
        }
    }

    // This is the lighting animation.
    if (lighting_index > 0) {
        lighting_index++;
        lighting_index %= 33;
        if (lighting_index <= 11) {
            bot_status = bot_lit_1;
        } else if (lighting_index > 11 && lighting_index < 22) {
            bot_status = bot_lit_2;
        } else {
            bot_status = bot_lit_1;
        }
        m_map->light_lit(m_bot->current_position());
    }

    tx[bot_status].Draw(
        plt_center + cst::cell_pos_delta_x * m_bot->current_position().x +
        cst::cell_pos_delta_y * m_bot->current_position().y +
        cst::cell_pos_delta_h * m_bot->current_position().h + bot_pos_delta);

    for (int i = 0; i < m_map->light_count(); i++) {
        if (m_map->lights()[i].pos > m_bot->current_position()) {
            continue;
        }
        if (m_map->lights()[i].turned_on) {
            tx[light_lit].Draw(
                plt_center + cst::cell_pos_delta_x * m_map->lights()[i].pos.x +
                cst::cell_pos_delta_y * m_map->lights()[i].pos.y +
                cst::light_delta);
        } else {
            tx[light].Draw(plt_center +
                           cst::cell_pos_delta_x * m_map->lights()[i].pos.x +
                           cst::cell_pos_delta_y * m_map->lights()[i].pos.y +
                           cst::light_delta);
        }
    }

    for (int i = 0; i < m_map->cells_count(); i++) {
        if (!(m_map->cells()[i].pos > m_bot->current_position())) {
            continue;
        }
        tx[cell].Draw(plt_center +
                      cst::cell_pos_delta_x * m_map->cells()[i].pos.x +
                      cst::cell_pos_delta_y * m_map->cells()[i].pos.y +
                      cst::cell_pos_delta_h * m_map->cells()[i].pos.h);
    }
    // This draws the cells above the bot.

    return;
}

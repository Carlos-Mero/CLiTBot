// this is the module that draws and outputs the map of the game.

#include "const.h"
#include "struct.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

// MARK: Standard features

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

  pix **pic = new pix *[cst::SCREEN_WIDTH - cst::WIDGET_WIDTH];
  for (int i = 0; i < cst::SCREEN_WIDTH - cst::WIDGET_WIDTH; i++) {
    pic[i] = new pix[cst::SCREEN_HEIGHT];
    for (int j = 0; j < cst::SCREEN_HEIGHT; j++) {
      pic[i][j] = cst::background_color;
    }
  }
  // This initializes the picture in the main memory.

  Position plt_st = m_bot->current_position();
  // Set the position of the bot as the center of the whole picture.

  for (int i = 0; i < m_map->cells_count(); i++) {
    Position paint_pos = m_map->cells()[i].pos;
    // Get the position of the cell.
    paint_pos.x -= plt_st.x;
    paint_pos.y -= plt_st.y;
    // Get the relative position of the cells.
    paint_pos.x = paint_pos.x + paint_pos.y;
    paint_pos.y = paint_pos.x - paint_pos.y * 2;
    // Transfers the position of the cell to a 2.5D view.

    if (paint_pos.x >= -cst::max_cells_l / 2 &&
        paint_pos.x <= cst::max_cells_l / 2 &&
        paint_pos.y >= -cst::max_cells_w / 2 &&
        paint_pos.y <= cst::max_cells_w / 2) {
      int paint_center_l = paint_pos.x * cst::cell_length / 2 +
                           (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH) / 2;

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
               y <= paint_center_w - paint_width_expansion - 1; y--) {

            if (y < 0 || y > cst::SCREEN_HEIGHT) {
              continue;
            } else {
              pic[x][y] = cst::grey_blue;
            }
          }

          for (int k = 0; k < paint_pos.h; k++) {

            for (int y = paint_center_w - paint_width_expansion -
                         k * cst::cell_height - 1;
                 y >= paint_center_w - paint_width_expansion -
                          (k + 1) * cst::cell_height;
                 y--) {

              if (y < 0 || y > cst::SCREEN_HEIGHT) {
                continue;
              } else {
                if (x < paint_center_l && paint_width_expansion != 0) {
                  pic[x][y] = cst::grey_blue;
                } else if (x > paint_center_l && paint_width_expansion != 0) {
                  pic[x][y] = cst::dark_grey;
                } else {
                  pic[x][y] = cst::dark_line;
                }
              }
            }
          }
          pic[x][paint_center_w + paint_width_expansion] = cst::dark_line;
          pic[x][paint_center_w - paint_width_expansion] = cst::dark_line;
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
           (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH - cst::bot_width_pixels) / 2;
       x <= (cst::SCREEN_WIDTH - cst::WIDGET_WIDTH + cst::bot_width_pixels) /
                2 &&
       !bot_img.eof();
       x++) {
    for (int y = (cst::SCREEN_HEIGHT + cst::bot_height_pixels) / 2;
         y >= (cst::SCREEN_HEIGHT - cst::bot_height_pixels) / 2 &&
         !bot_img.eof();
         y--) {
      bot_img.read((char *)&current_pixel, sizeof(pix));
      if (current_pixel.green == cst::white_pix.green &&
          current_pixel.blue == cst::white_pix.blue &&
          current_pixel.red == cst::white_pix.red) {
        continue;
      } else {
        pic[x][y] = current_pixel;
      }
    }
  }

  for (int x = 0; x < cst::SCREEN_WIDTH - cst::WIDGET_WIDTH; x++) {
    mapfile.write((char *)pic[x], cst::SCREEN_HEIGHT * sizeof(pix));
  }
  // This draws the picture to the file.

  mapfile.close();
  bot_img.close();
  for (int i = 0; i < cst::SCREEN_WIDTH - cst::WIDGET_WIDTH; i++) {
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
    op_map(std::to_string(m_auto_save_id));
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
             cst::message_start_pos.GetY() + (i + 1) * cst::char_height_18, 14,
             (i == (command_list_index % cst::CMD_list_max_len))
                 ? cst::textcolor
                 : cst::raylightblue);

    DrawText(command_lists[i], 26.0f,
             cst::message_start_pos.GetY() + (i + 1) * cst::char_height_18, 18,
             (i + 1 == (command_list_index % cst::CMD_list_max_len))
                 ? cst::textcolor
                 : cst::raylightblue);
  }

  return;
}

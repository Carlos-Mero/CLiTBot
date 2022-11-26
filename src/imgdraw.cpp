// this is the module that draws and outputs the map of the game.

#include "struct.h"
#include "const.h"
#include <fstream>
#include <iostream>
#include <string>

void Game::op_map(std::string file_name){
    // This function draws and saves the map of the game.
    std::ofstream mapfile;
    mapfile.open(cst::SAVE_PATH + file_name, std::ios::binary);
    // Warning! This method will open the file and wipe all the content existing there! But for our purpose of saving the map, it's just fine.
	
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
    
    if(!mapfile.is_open()||!bot_img.is_open()){
        mapfile.close();
		bot_img.close();
        std::cout << "发生了一些意外……文件没能正常打开？！" << std::endl;
        return;
    }
    
    mapfile.write((char *)&cst::BFH, sizeof(cst::BFH));
    mapfile.write((char *)&cst::BIH, sizeof(cst::BIH));
    // Here we write in the header of the picture.
	
	pix ** pic = new pix * [cst::SCREEN_WIDTH-cst::WIDGET_WIDTH];
	for(int i = 0; i < cst::SCREEN_WIDTH-cst::WIDGET_WIDTH; i++){
		pic[i] = new pix[cst::SCREEN_HEIGHT];
		for(int j = 0; j < cst::SCREEN_HEIGHT; j++){
			pic[i][j] = cst::background_color;
		}
	}
	// This initializes the picture in the main memory.
	
    Position plt_st = m_bot->current_position();
    // Set the position of the bot as the center of the whole picture.
	
	for(int i = 0; i < m_map->cells_count(); i++){
		Position paint_pos = m_map->cells()[i].pos;
		// Get the position of the cell.
		paint_pos.x -= plt_st.x;
		paint_pos.y -= plt_st.y;
		// Get the relative position of the cells.
		paint_pos.x = paint_pos.x + paint_pos.y;
		paint_pos.y = paint_pos.x - paint_pos.y * 2;
		// Transfers the position of the cell to a 2.5D view.
		
		if (paint_pos.x >= -cst::max_cells_l/2 && paint_pos.x <= cst::max_cells_l/2 && paint_pos.y >= -cst::max_cells_w/2 && paint_pos.y <= cst::max_cells_w/2) {
			
			for(int x = (paint_pos.x-1) * cst::cell_length/2 + (cst::SCREEN_WIDTH-cst::WIDGET_WIDTH)/2; x <= (paint_pos.x+1) * cst::cell_length/2 + (cst::SCREEN_WIDTH-cst::WIDGET_WIDTH)/2; x++){
				
				if (x < 0 || x > cst::SCREEN_WIDTH - cst::WIDGET_WIDTH) {
					continue;
				}else{
					for(int y = (paint_pos.y-1) * cst::cell_width/2 + cst::SCREEN_HEIGHT/2; y <= (paint_pos.y+1) * cst::cell_width + cst::SCREEN_HEIGHT/2; y++){
						
						
						
					}
				}
			}
		}else{
			continue;
		}
	}
	
	for(int x = 0; x < cst::SCREEN_WIDTH-cst::WIDGET_WIDTH; x++){
		mapfile.write((char *)pic[x], cst::SCREEN_HEIGHT * sizeof(pix));
	}
	// This draws the picture to the file.
    
    mapfile.close();
	bot_img.close();
	for(int i = 0; i < cst::SCREEN_WIDTH-cst::WIDGET_WIDTH; i++){
		delete [] pic[i];
	}
	delete [] pic;
	// release the memory occupied by the pointer.
    
    std::cout << "当前地图已输出！" << std::endl;
    
    return;
}

void Game::auto_op_map(){
    // This function automatically saves and outputs the condition of the map.
    
    return;
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game_window.h
 * Author: kinsey40
 *
 * Created on 10 January 2018, 22:52
 */

#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>
#include "draw_line.h"
#include "row.h"

class Game_Window: public Fl_Double_Window
{
public:
    Game_Window(int w, int h, const char* n);
    void show_window(std::vector<int> data);
    void hide_window();
    void add_vertical_lines();
    void add_horizontal_lines();
    void draw_numbers();
    void add_rows();
    void delete_everything();
    int get_pin_width() const;
    
    
private:
    int width;
    int height;
    int no_of_pins;
    int no_of_allowed_guesses;
    int no_of_colour_options;
    int first_x_coord;
    int second_x_coord;
    int first_y_coord;
    int second_y_coord;
    int y_coord;
    
    const int pin_width;
    const char* name;
    
    Draw_Line* v_line_1;
    Draw_Line* v_line_2;
    
    std::vector<int> d;
    
    std::vector<Fl_Text_Buffer*> numbers;
    std::vector<Fl_Text_Display*> disps;
    std::vector<Draw_Line*> lines;
    
    
    
};

#endif /* GAME_WINDOW_H */
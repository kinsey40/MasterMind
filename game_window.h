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
#include "settings_window.h"
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
    void add_other_buttons();
    void advance_row();
    bool get_guess();
    int get_pin_width() const;
    int get_result_width() const;
    void generate_answer();
    bool evaluate_guess();
    void game_win();
    void game_lost();
    static void check_but_cb(Fl_Widget* obj, Game_Window* win);
    static void win_cb(Fl_Widget* obj, Game_Window* win);
    static void c_settings_but_cb(Fl_Widget* obj, Game_Window* win);
    static void quit_but_cb(Fl_Widget* obj, Game_Window* win);
    static void reset_but_cb(Fl_Widget* obj, Game_Window* win);
    static void set_static_data(std::vector<int> d);
    void reset_win();
    
    
    
private:
    int width;
    int height;
    int no_of_pins;
    int no_of_allowed_guesses;
    int no_of_colour_options;
    int second_x_coord;
    int second_y_coord;
    int third_x_coord;
    int third_y_coord;
    int y_coord;
    int current_row;
    int right_place;
    int wrong_place;
    int g_count;
    int a_count;
    static bool window_already_open;
    
    const int first_x_coord;
    const int first_y_coord;
    const int pin_width;
    const int o_but_width;
    const int o_but_height;
    const int result_width;
    
    const char* name;
    
    std::vector<int> d;
    std::vector<int> current_guess;
    std::vector<int> answers;
    std::vector<int> incorrect_guess_places;
    std::vector<int> incorrect_answer_places;
    static std::vector<int> static_data;
    
    std::vector<Fl_Text_Buffer*> numbers;
    std::vector<Fl_Text_Display*> disps;
    std::vector<Draw_Line*> lines;
    std::vector<Row*> rows_vec;
    
    Fl_Button* reset_but;
    Fl_Button* quit_but;
    Fl_Button* c_settings_but;
    Fl_Button* check_but;
    
};

#endif /* GAME_WINDOW_H */
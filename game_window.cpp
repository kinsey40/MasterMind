/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game_window.cpp
 * Author: kinsey40
 * 
 * Created on 10 January 2018, 22:52
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <typeinfo>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Line_Dial.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include "game_window.h"
#include "settings_window.h"

bool Game_Window::window_already_open = false;
std::vector<int> Game_Window::static_data;

Game_Window::Game_Window(int w, int h, const char* n)
    : Fl_Double_Window(w, h, n),
      width(w),
      height(h),
      name(n),
      pin_width(100),
      result_width(30),
      first_x_coord(30),
      first_y_coord(50),
      o_but_width(80),
      o_but_height(30)
{
}

void Game_Window::show_window(std::vector<int> data)
{   
    std::srand(time(NULL));
    set_static_data(data);

    if(window_already_open == false){
        d.clear();
        d = data;
        no_of_pins = data[0];
        no_of_colour_options = data[1];
        no_of_allowed_guesses = data[2];
    
        window_already_open = true;
        current_row = 0;
    
        this->begin();

        generate_answer();
        add_vertical_lines();
        add_horizontal_lines();
        draw_numbers();
        add_rows();
        add_other_buttons();

        this->callback((Fl_Callback*) win_cb, this);
        this->end();
        this->show();

    }
}


void Game_Window::hide_window()
{
    this->hide();
    window_already_open = false;
}


void Game_Window::add_vertical_lines()
{   
    second_x_coord = (no_of_pins * get_pin_width() + first_x_coord);
    second_y_coord = first_y_coord * (no_of_allowed_guesses + 2);
    third_x_coord = second_x_coord + (no_of_pins * get_result_width());
    
    Draw_Line* v_line_1 = new Draw_Line(first_x_coord, first_y_coord, first_x_coord, second_y_coord, NULL);
    Draw_Line* v_line_2 = new Draw_Line(second_x_coord, first_y_coord, second_x_coord, second_y_coord, NULL);
    Draw_Line* v_line_3 = new Draw_Line(third_x_coord, first_y_coord, third_x_coord, second_y_coord, NULL);
    
    lines.push_back(v_line_1);
    lines.push_back(v_line_2);
    lines.push_back(v_line_3);
    
}


void Game_Window::add_horizontal_lines()
{
    for(int i=0; i<=(no_of_allowed_guesses + 1); i++) {
        y_coord = first_y_coord * (i+1);
        Draw_Line* line = new Draw_Line(first_x_coord, y_coord, \
            third_x_coord, y_coord, NULL);
        lines.push_back(line);
    }
    
}

int Game_Window::get_pin_width() const 
{
    return pin_width;
}

int Game_Window::get_result_width() const
{
    return result_width;
}


void Game_Window::draw_numbers()
{
    for(int i=0; i<=no_of_allowed_guesses; i++){
        const char* input;
        int x = i + 1;
        
        if(i == no_of_allowed_guesses) {
            input = "Ans";
        }
        else {
            switch(x) {
                case 1:
                    input = "1.";
                    break;
                case 2:
                    input = "2.";
                    break;
                case 3:
                    input = "3.";
                    break;
                case 4:
                    input = "4.";
                    break;
                case 5:
                    input = "5.";
                    break;
                case 6:
                    input = "6.";
                    break;
                case 7:
                    input = "7.";
                    break;
                case 8:
                    input = "8.";
                    break;
                case 9:
                    input = "9.";
                    break;
                case 10:
                    input = "10.";
                    break;
                default:
                    input="N/A";
            }
        }
        Fl_Box* b = new Fl_Box(2, ((i+1)*first_y_coord), (first_x_coord - 5), first_y_coord, input);
        b->box(FL_FLAT_BOX);
    }
}


void Game_Window::add_rows()
{
    for(int i=0; i<=no_of_allowed_guesses; i++){
        int y_val = (i+1)*first_y_coord;
        Row* obj;
        
        if(i == no_of_allowed_guesses) {
            obj = new Row(d, first_y_coord, first_x_coord, second_x_coord, pin_width, y_val, result_width, true);
        }
        else {
            obj = new Row(d, first_y_coord, first_x_coord, second_x_coord, pin_width, y_val, result_width);
        }
        
        rows_vec.push_back(obj);
    }
    
    rows_vec[current_row] -> unfreeze();
}


void Game_Window::advance_row()
{
    rows_vec[current_row] -> freeze();
    current_row++;
    rows_vec[current_row] -> unfreeze();
}


bool Game_Window::get_guess()
{
    current_guess = rows_vec[current_row] -> get_guess();
    bool incomplete = false;
    int checker = 0;
    
    for(int i=0; i<current_guess.size(); i++){
        checker = current_guess[i];
        if(checker == 0){
            incomplete = true;
            break;
        }
    }
    
    return incomplete;
}


void Game_Window::add_other_buttons()
{
    int check_x_coord = (second_x_coord + first_x_coord - o_but_width) / 2; 
    int check_y_coord = first_y_coord * (no_of_allowed_guesses + 2) + 10;
    
    int reset_x_coord = first_x_coord;
    int reset_y_coord = 10;
   
    int quit_x_coord = this->w() - first_x_coord - o_but_width;
    int quit_y_coord = 10;
    
    int c_settings_x_coord = ((quit_x_coord + (reset_x_coord + o_but_width)) / 2) - o_but_width;
    int c_settings_y_coord = 10 ;
    
    check_but = new Fl_Button(check_x_coord, check_y_coord, o_but_width, o_but_height, "Check");
    check_but -> callback((Fl_Callback*) check_but_cb, this);
    this->add(check_but);
    
    reset_but = new Fl_Button(reset_x_coord, reset_y_coord, o_but_width, o_but_height, "Reset");
    reset_but -> callback((Fl_Callback*) reset_but_cb, this);
    this->add(reset_but);
    
    quit_but = new Fl_Button(quit_x_coord, quit_y_coord, o_but_width, o_but_height, "Quit");
    quit_but -> callback((Fl_Callback*) quit_but_cb, this);
    this->add(quit_but);
    
    c_settings_but = new Fl_Button(c_settings_x_coord, c_settings_y_coord, o_but_width*2, o_but_height, "Change Settings");
    c_settings_but -> callback((Fl_Callback*) c_settings_but_cb, this);
    this->add(c_settings_but);
}


void Game_Window::check_but_cb(Fl_Widget* obj, Game_Window* win)
{
    bool incom;
    incom = win->get_guess();
    
    if(incom == false){
        bool g_over = win->evaluate_guess();
        if(g_over == false) win->advance_row();
    }
}

void Game_Window::set_static_data(std::vector<int> d)
{
    Game_Window::static_data = d;
}


void Game_Window::reset_but_cb(Fl_Widget* obj, Game_Window* win)
{
    win->reset_win();
}


void Game_Window::reset_win()
{
    this->hide();
    Settings_Window* upper_win = (Settings_Window*) Fl::first_window();
    
    window_already_open = false;
    upper_win ->launch_game();
    
}


void Game_Window::quit_but_cb(Fl_Widget* obj, Game_Window* win)
{
    Fl::first_window()->hide();
    Fl::next_window(Fl::first_window())->hide();
}


void Game_Window::c_settings_but_cb(Fl_Widget* obj, Game_Window* win)
{
    static_data.clear();
    window_already_open = false;
    win->hide();
}

void Game_Window::generate_answer()
{
    answers.clear();
    for(int i=0; i < no_of_pins; i++){
        answers.push_back((rand() % no_of_colour_options) + 1);
        std::cout << answers[i] << std::endl;
    }
}


bool Game_Window::evaluate_guess()
{
    right_place = 0;
    wrong_place = 0;

    incorrect_guess_places.clear();
    incorrect_answer_places.clear();
    passing_guess.clear();
    
    assert(no_of_pins == current_guess.size());
    assert(no_of_pins == answers.size());

    for(int j=0; j < no_of_pins; j++) {
        if(answers[j] == current_guess[j]) {
            right_place += 1;
        }
        else {
            incorrect_guess_places.push_back(current_guess[j]);
            incorrect_answer_places.push_back(answers[j]);
        }
    }
    
    for(int j=1; j < (no_of_colour_options + 1); j++) {
        g_count = 0;
        a_count = 0;

        g_count = std::count(incorrect_guess_places.begin(), incorrect_guess_places.end(), j);
        a_count = std::count(incorrect_answer_places.begin(), incorrect_answer_places.end(), j);

        if(a_count > 0) {
            if(g_count <= a_count) {
                wrong_place += g_count;
            }
            else {
                wrong_place += a_count;
            }
        }
    }
    
    for(int i=0; i < right_place; i++) {
        passing_guess.push_back(1);
    }
    
    for(int i=0; i < wrong_place; i++) {
        passing_guess.push_back(0);
    }
    
    for(int i=0; i < no_of_pins - (right_place + wrong_place); i++) {
        passing_guess.push_back(-1);
    }
    
    rows_vec[current_row] -> reveal_result(passing_guess);
    bool game_over = true;
    
    if(right_place == no_of_pins) {
        game_win();
    }
    else if(current_row >= no_of_allowed_guesses-1) {
        game_lost();
    }
    else {
        game_over = false;
    }

    return game_over;
}


void Game_Window::game_win()
{
    std::cout << "You Won!" << std::endl;
    for(int i=0; i<no_of_allowed_guesses; i++){
        rows_vec[i] -> freeze();    
    }
    rows_vec[no_of_allowed_guesses] -> reveal(answers);
}

void Game_Window::game_lost()
{
    std::cout << "You Lost!" << std::endl;
    for(int i=0; i<no_of_allowed_guesses; i++){
        rows_vec[i] -> freeze();    
    }
    rows_vec[no_of_allowed_guesses] -> reveal(answers);
}


void Game_Window::win_cb(Fl_Widget* obj, Game_Window* win)
{
    window_already_open = false;
    win->hide();
}

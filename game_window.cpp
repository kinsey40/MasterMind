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
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Line_Dial.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>
#include "game_window.h"


Game_Window::Game_Window(int w, int h, const char* n)
    : Fl_Double_Window(w, h, n),
      width(w),
      height(h),
      name(n),
      pin_width(100),
      first_x_coord(50),
      first_y_coord(50),
      c_but_width(80),
      c_but_height(50)
{
}

void Game_Window::show_window(std::vector<int> data)
{
    d = data;
    no_of_pins = data[0];
    no_of_colour_options = data[1];
    no_of_allowed_guesses = data[2];
    current_row = 0;
    
    std::srand(time(NULL));
    
    this->begin();
    generate_answer();
    add_vertical_lines();
    add_horizontal_lines();
    draw_numbers();
    add_rows();
    add_check_button();
    this->end();
    this->show();
}

void Game_Window::hide_window()
{
    delete_everything();
    this->hide();
}


void Game_Window::add_vertical_lines()
{   
    second_x_coord = (no_of_pins * get_pin_width() + first_x_coord);
    second_y_coord = first_y_coord * (no_of_allowed_guesses + 2);
    
    v_line_1 = new Draw_Line(first_x_coord, first_y_coord, first_x_coord, second_y_coord, NULL);
    v_line_2 = new Draw_Line(second_x_coord, first_y_coord, second_x_coord, second_y_coord, NULL);
    
}


void Game_Window::add_horizontal_lines()
{
    for(int i=0; i<=(no_of_allowed_guesses + 1); i++) {
        y_coord = first_y_coord * (i+1);
        Draw_Line* line = new Draw_Line(first_x_coord, y_coord, \
            second_x_coord, y_coord, NULL);
        lines.push_back(line);
    }
    
}

int Game_Window::get_pin_width() const 
{
    return pin_width;
}

void Game_Window::draw_numbers()
{
    for(int i=0; i<=no_of_allowed_guesses; i++){
        const char* input;
        
        if(i == no_of_allowed_guesses) {
            input = "Ans";
        }
        else {
            std::ostringstream ostr;
            ostr << i+1;
            input = ostr.str().c_str();
        }
    
        Fl_Text_Buffer* buff = new Fl_Text_Buffer();
        Fl_Text_Display* disp = new Fl_Text_Display(5, ((i+1)*first_y_coord + 10), 40, 30, NULL);
        
        numbers.push_back(buff);
        disps.push_back(disp);
        
        disp->buffer(buff);
        buff->text(input);
    }
    
    
}


void Game_Window::add_rows()
{
    for(int i=0; i<no_of_allowed_guesses; i++){
        int y_val = (i+1)*first_y_coord;
        Row* obj = new Row(d, first_y_coord, first_x_coord, pin_width, y_val);
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


void Game_Window::add_check_button()
{
    int check_x_coord = second_x_coord + ((this->w() - second_x_coord - c_but_width) / 2);
    int check_y_coord = first_y_coord;
    
    check_but = new Fl_Button(check_x_coord, check_y_coord, c_but_width, c_but_height, "Check");
    check_but -> callback((Fl_Callback*) check_but_cb, this);
    this->add(check_but);
}


void Game_Window::check_but_cb(Fl_Widget* obj, Game_Window& win)
{
    bool incom;
    incom = win.get_guess();
    
    if(incom == false){
        win.evaluate_guess();
        win.advance_row();
    }
}

void Game_Window::generate_answer()
{
    answers.clear();
    for(int i=0; i < no_of_pins; i++){
        answers.push_back((rand() % (no_of_colour_options - 1)) + 1);
    }
}



void Game_Window::evaluate_guess()
{
    right_place = 0;
    wrong_place = 0;

    incorrect_guess_places.clear();
    incorrect_answer_places.clear();
    
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

    std::cout << "Row No." << current_row << " Right: " << right_place << " " << "Wrong: " << wrong_place << std::endl;

    if(right_place == no_of_pins) {
        game_win();
    }
    else if(current_row >= no_of_allowed_guesses) {
        game_lost();
    }
    else {
    }

}


void Game_Window::game_win()
{
    std::cout << "You Won!" << std::endl;
    rows_vec[current_row] -> freeze();
}

void Game_Window::game_lost()
{
    std::cout << "You Lost!" << std::endl;
    rows_vec[current_row] -> freeze();
}


void Game_Window::delete_everything()
{
    Fl::delete_widget(v_line_1);
    Fl::delete_widget(v_line_2);
    v_line_1, v_line_2 = NULL;
    
    for(int i=0; i<=no_of_allowed_guesses; i++){
        Fl_Text_Buffer* n = numbers[i];
        Fl_Text_Display* d = disps[i];
        Draw_Line* l = lines[i];
        
        Fl::delete_widget(l);
        Fl::delete_widget(d);
        n->remove_selection();
        n, d, l = NULL;
    }
}
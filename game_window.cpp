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
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Line_Dial.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>
#include "game_window.h"


Game_Window::Game_Window(int w, int h, const char* n)
:
Fl_Double_Window(w, h, n),
width(w),
height(h),
name(n),
pin_width(100)
{
}

void Game_Window::show_window(std::vector<int> data)
{
    d = data;
    no_of_pins = data[0];
    no_of_colour_options = data[1];
    no_of_allowed_guesses = data[2];
    
    this->begin();
    add_vertical_lines();
    add_horizontal_lines();
    draw_numbers();
    add_rows();
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
    first_y_coord = 50;
    first_x_coord = 50;
    
    second_x_coord = no_of_pins * get_pin_width();
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
    // Call an instance of the rows class
    Row obj(d);
    
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
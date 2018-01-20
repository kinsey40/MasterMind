/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   settings_window.cpp
 * Author: kinsey40
 * 
 * Created on 10 January 2018, 22:22
 */

#include <iostream>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include "settings_window.h"
#include "game_window.h"


Game_Window Settings_Window::game(600, 650, "Game");
int Settings_Window::no_of_windows = 0;


Settings_Window::Settings_Window(int w, int h, const char* n)
: 
Fl_Window(w, h, n),
width(w),
height(h),
name(n)
{
    set_no_of_pins();
    set_no_of_colour_options();
    set_no_of_allowed_guesses();
    
    this->callback((Fl_Callback*) win_cb);
    this->begin();
    this->end();
    populate_window();
    populate_data();
    this->show();
}


int Settings_Window::set_no_of_pins()
{
    no_of_pins = 4;
    return no_of_pins;
}


int Settings_Window::set_no_of_allowed_guesses()
{
    no_of_allowed_guesses = 10;
    return no_of_allowed_guesses;
}


int Settings_Window::set_no_of_colour_options()
{
    no_of_colour_options = 4;
    return no_of_colour_options;
}

void Settings_Window::populate_data()
{
    data.push_back(no_of_pins);
    data.push_back(no_of_colour_options);
    data.push_back(no_of_allowed_guesses);
}

void Settings_Window::populate_window()
{   
    but = new Fl_Button(20, 40, 300, 100, "Launch");
    but -> callback((Fl_Callback*) launch_cb, &data);
    this->add(but);
    
}


void Settings_Window::launch_cb(Fl_Widget* obj, std::vector<int> data)
{
    
    //if(no_of_windows == 0){
    //    game.show_window(*data);
    //}
    
    no_of_windows++;
    game.show_window(data);
}

void Settings_Window::win_cb(Fl_Widget* obj, void*)
{
    game.hide_window();
    Fl_Window* win = (Fl_Window*)obj;
    win->hide();
}
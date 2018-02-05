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
#include <FL/Fl_Choice.H>
#include "settings_window.h"
#include "game_window.h"

static Game_Window* game;

Settings_Window::Settings_Window(int w, int h, const char* n)
: 
Fl_Window(w, h, n),
width(w),
height(h),
name(n)
{
    set_starting_values();
    
    this->callback((Fl_Callback*) win_cb, this);
    this->begin();
    this->end();
    populate_window();
    this->show();
}


void Settings_Window::set_starting_values()
{
    no_of_pins = 4;
    no_of_allowed_guesses = 10;
    no_of_colour_options = 4;
    
}

void Settings_Window::populate_data()
{
    data.clear();
    data.push_back(no_of_pins);
    data.push_back(no_of_colour_options);
    data.push_back(no_of_allowed_guesses);
}

void Settings_Window::populate_window()
{   
    int but_width = 80;
    int but_height = 50;
    
    int width = (this->w() / 2) - (but_width / 2);
    int height = 250;
    
    int l_width = 80;
    int l_height = 20;
    
    int l_gap = 15;
    
    int x_value = (this->w() / 2) - (l_width / 2);
    
    int first_y_val = 140;
    int second_y_val = first_y_val + (1 * (l_height + l_gap));
    int third_y_val = first_y_val + (2 * (l_height + l_gap));
    
    but = new Fl_Button(width, height, but_width, but_height, "Launch");
    but -> callback((Fl_Callback*) launch_cb, this);
    
    label_no_of_pins = new Fl_Choice(x_value, first_y_val, l_width, l_height, "No. of pins:");
    label_no_of_pins->add("3", 0, (Fl_Callback*) no_of_pins_3_cb, this, 0);
    label_no_of_pins->add("4", 0, (Fl_Callback*) no_of_pins_4_cb, this, 0);
    label_no_of_pins->add("5", 0, (Fl_Callback*) no_of_pins_5_cb, this, 0);
    
    label_no_of_allowed_guesses = new Fl_Choice(x_value, second_y_val, l_width, l_height, "No. of guesses:");
    label_no_of_allowed_guesses->add("8", 0, (Fl_Callback*) no_of_allowed_guesses_8_cb, this, 0);
    label_no_of_allowed_guesses->add("9", 0, (Fl_Callback*) no_of_allowed_guesses_9_cb, this, 0);
    label_no_of_allowed_guesses->add("10", 0, (Fl_Callback*) no_of_allowed_guesses_10_cb, this, 0);
    
    label_no_of_colours = new Fl_Choice(x_value, third_y_val, l_width, l_height, "No. of colours:");
    label_no_of_colours->add("3", 0, (Fl_Callback*) no_of_colours_3_cb, this, 0);
    label_no_of_colours->add("4", 0, (Fl_Callback*) no_of_colours_4_cb, this, 0);
    label_no_of_colours->add("5", 0, (Fl_Callback*) no_of_colours_5_cb, this, 0);
    
    label_no_of_pins->value(1);
    label_no_of_allowed_guesses->value(2);
    label_no_of_colours->value(1);
    
    this->add(label_no_of_pins);
    this->add(label_no_of_allowed_guesses);
    this->add(label_no_of_colours);
    this->add(but);
}


void Settings_Window::launch_cb(Fl_Widget* obj, Settings_Window* win)
{   
    win->launch_game();
}


void Settings_Window::launch_game()
{
    populate_data();
    int w = 150 * no_of_pins;
    int h = (50 * no_of_allowed_guesses) + 150;
    
    game = new Game_Window(w, h, "Game");
    game->show_window(data);
}


void Settings_Window::win_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->close_all();
}


void Settings_Window::no_of_pins_3_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_pins = 3;
}


void Settings_Window::no_of_pins_4_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_pins = 4;
}


void Settings_Window::no_of_pins_5_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_pins = 5;
}


void Settings_Window::no_of_allowed_guesses_8_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_allowed_guesses = 8;
}


void Settings_Window::no_of_allowed_guesses_9_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_allowed_guesses = 9;
}


void Settings_Window::no_of_allowed_guesses_10_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_allowed_guesses = 10;
}


void Settings_Window::no_of_colours_3_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_colour_options = 3;
}


void Settings_Window::no_of_colours_4_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_colour_options = 4;
}


void Settings_Window::no_of_colours_5_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_colour_options = 5;
}


void Settings_Window::close_all()
{
    game -> hide_window();
    this -> hide();
}
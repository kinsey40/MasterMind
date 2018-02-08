/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   settings_window.h
 * Author: kinsey40
 *
 * Created on 10 January 2018, 22:22
 */

#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H


#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include "game_window.h"

class Settings_Window: public Fl_Window
{
public:
    Settings_Window(int w, int h, const char* n);
    void set_starting_values();
    void populate_window();
    void populate_data();
    
    static void no_of_pins_3_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_pins_4_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_pins_5_cb(Fl_Widget* obj, Settings_Window* win);
    
    static void no_of_allowed_guesses_8_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_allowed_guesses_9_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_allowed_guesses_10_cb(Fl_Widget* obj, Settings_Window* win);
    
    static void no_of_colours_3_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_colours_4_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_colours_5_cb(Fl_Widget* obj, Settings_Window* win);
    
    static void instructions_cb(Fl_Widget* obj, Settings_Window* win);
    static void win_i_cb(Fl_Widget* obj, Settings_Window* win);
    
    static void launch_cb(Fl_Widget* obj, Settings_Window* win);
    static void win_cb(Fl_Widget* obj, Settings_Window* win);
    
    void launch_game();
    void close_all();
    
    
private:
    const int width;
    const int height;
    const char* name;
    
    int no_of_pins;
    int no_of_allowed_guesses;
    int no_of_colour_options;
    int no_instruction_wins;
    
    std::vector<int> data;
    
    Fl_Box* message;
    Fl_Button* instructions;
    Fl_Button* but;
    Fl_Choice* label_no_of_pins;
    Fl_Choice* label_no_of_allowed_guesses;
    Fl_Choice* label_no_of_colours;
};


#endif /* SETTINGS_WINDOW_H */
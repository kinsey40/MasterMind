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

#include "game_window.h"

class Settings_Window: public Fl_Window
{
public:
    Settings_Window(int w, int h, const char* n);
    int set_no_of_pins();
    int set_no_of_allowed_guesses();
    int set_no_of_colour_options();
    void populate_window();
    void populate_data();
    static void launch_cb(Fl_Widget* obj, std::vector<int>);
    static void win_cb(Fl_Widget* obj, void*);
    
    
private:
    const int width;
    const int height;
    const char* name;
    
    int no_of_pins;
    int no_of_allowed_guesses;
    int no_of_colour_options;
    
    std::vector<int> data;
    
    Fl_Button* but;
};


#endif /* SETTINGS_WINDOW_H */
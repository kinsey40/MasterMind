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

class Settings_Window
{
public:
    Settings_Window();
    void populate_window();
    static void launch_cb(Fl_Widget* obj, void*);
    static void win_cb(Fl_Widget *widget, void*);
    static void set_wh_values();
    void set_difficulty();
    void check_game_state();
    ~Settings_Window();

private:
    int difficulty;
    const int no_of_pins;
    const int no_of_allowed_guesses;
    const int width;
    const int height;
    
    static const int g_width;
    static const int g_height;
    
    Fl_Window* window;
    Fl_Button* but;
    
    static Game_Window game;
    
    
};


#endif /* SETTINGS_WINDOW_H */
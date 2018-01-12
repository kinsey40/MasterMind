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
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include "settings_window.h"
#include "game_window.h"

//const int Settings_Window::g_width = 400;
//const int Settings_Window::g_height = 400;
Game_Window Settings_Window::game;


Settings_Window::Settings_Window()
:   no_of_pins(4),
    no_of_allowed_guesses(10),
    width(340),
    height(180)
{
    window = new Fl_Window(width, height);
    window->callback(win_cb);
    window->begin();
        populate_window();
    window->end();
    window->show();
}


void Settings_Window::set_difficulty()
{
    difficulty = 4;
}

void Settings_Window::populate_window()
{
    but = new Fl_Button(20, 40, 300, 100, "Launch");
    but->callback((Fl_Callback*) launch_cb);
    window->add(but);
}

void Settings_Window::launch_cb(Fl_Widget* obj, void*)
{
    game.show_game();
}

void Settings_Window::win_cb(Fl_Widget* widget, void *)
{
    Fl_Window* win = (Fl_Window*)widget;
    win->hide();
    game.hide_game();
    
}

Settings_Window::~Settings_Window()
{
}
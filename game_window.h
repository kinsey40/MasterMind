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

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

class Game_Window
{
public:
    Game_Window();
    void delete_window();
    Fl_Window* game_address();
    void hide_game();
    void show_game();
    ~Game_Window();
    
private:
    Fl_Window* window;
    int w;
    int h;
    
    
};

#endif /* GAME_WINDOW_H */
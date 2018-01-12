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

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

class Game_Window: public Fl_Window
{
public:
    Game_Window(int w, int h, const char* n);
    void show_window(std::vector<int> data);
    void hide_window();
    
    
private:
    int width;
    int height;
    const char* name;
    
    
};

#endif /* GAME_WINDOW_H */
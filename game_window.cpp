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
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include "game_window.h"


Game_Window::Game_Window(int w, int h, const char* n)
:
Fl_Window(w, h, n),
width(w),
height(h),
name(n)
{
}

void Game_Window::show_window(std::vector<int> data)
{
    for(int i = 0; i < data.size(); i++) {
        std::cout << data[i] << std::endl;
    }	
    
    this->begin();
    this->end();
    this->show();
}

void Game_Window::hide_window()
{
    this->hide();
}


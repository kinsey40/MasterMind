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

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include "game_window.h"


Game_Window::Game_Window()
{
    
    
    window = new Fl_Window(340, 280);
    window->begin();
    window->end();
    hide_game();
}


void Game_Window::hide_game()
{
    window->hide();
}

void Game_Window::show_game()
{
    window->show();
}





Game_Window::~Game_Window()
{
    
}
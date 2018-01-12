/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kinsey40
 *
 * Created on 10 January 2018, 21:19
 */

#include <cstdlib>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include "settings_window.h"


int main() 
{
    Settings_Window obj;
    return Fl::run();
}
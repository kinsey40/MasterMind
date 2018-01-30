/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   square.cpp
 * Author: kinsey40
 * 
 * Created on 19 January 2018, 21:06
 */

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include "square.h"


Square::Square(int x, int y, int w, int h, int no_of_color_options, bool f, bool a)
:
Fl_Box(FL_UP_BOX, x, y, w, h, ""),
x_val(x), 
y_val(y),
width(w),
height(h),
no_colors(no_of_color_options),
frozen(f),
answer(a)
{
    no_of_clicks = 0;
    if(a == true){
        this->hide();
    }
        
}


int Square::handle(int e)
{   
    if(frozen == true){
        return 1;
    }
    
    switch(e) {
        case FL_RELEASE:
            no_of_clicks++;
            
            if(no_of_clicks >= no_colors + 1) {
                no_of_clicks = 1;
            }
            
            colour();
            
        default:
            return Fl_Box::handle(e);
    }
}


int Square::get_number_of_clicks()
{
    return no_of_clicks;
}


void Square::unfreeze()
{
    frozen = false;
}


void Square::freeze()
{
    frozen = true;
}


void Square::reveal(int data)
{
    no_of_clicks = data;
    colour();
}


int Square::colour()
{
    switch(no_of_clicks) {
        case 1:
            color(FL_BLUE);
            redraw();
            return 1;

        case 2:
            color(FL_RED);
            redraw();
            return 1;

        case 3:
            color(FL_GREEN);
            redraw();
            return 1;

        case 4:
            color(FL_MAGENTA);
            redraw();
            return 1;

        case 5:
            color(FL_BLACK);
            redraw();
            return 1;

        case 6:
            color(FL_CYAN);
            redraw();
            return 1;

        default:
            color(FL_GRAY);
            redraw();
            return 1;
    }
}


void Square::reveal_result(int data)
{
    v = data;
    set_answer_colour();
}


int Square::set_answer_colour()
{
    switch(v) {
        case 0:
            color(FL_BLACK);
            redraw();
            this->show();
            return 1;
        
        case 1:
            color(FL_WHITE);
            redraw();
            this->show();
            return 1;
            
        default:
            color(FL_GRAY);
            redraw();
            return 1;
    }
}
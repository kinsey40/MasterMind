/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   draw_line.cpp
 * Author: kinsey40
 * 
 * Created on 16 January 2018, 21:47
 */

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "draw_line.h"
#include <iostream>
#include <FL/Fl_Window.H>


Draw_Line::Draw_Line(int X, int Y, int X2, int Y2, const char* L=0)
:Fl_Widget(X,Y,X2,Y2,L),
x1(X),
y1(Y),
x2(X2),
y2(Y2)
{
    draw();
}
        
        
void Draw_Line::draw() 
{
    fl_color(FL_BLACK);
    fl_line(x1, y1, x2, y2);
}

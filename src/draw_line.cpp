/*
 * The MIT License
 *
 * Copyright 2018 kinsey40.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   draw_line.cpp
 * Author: kinsey40
 * 
 * Created on 16 January 2018, 21:47
 * 
 * The source file for the Draw_Line class, allowing the user to draw a line to 
 * the relevant FLTK window
 */


#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include "draw_line.h"


/* Constructor */
Draw_Line::Draw_Line(int X, int Y, int X2, int Y2, bool thick, const char* L=0)
:Fl_Widget(X,Y,X2,Y2,L),
x1(X),
y1(Y),
x2(X2),
y2(Y2),
t(thick)
{
    draw();
}
        

/* Overloading the draw function from the FL_Widget class */
void Draw_Line::draw() 
{
    fl_color(FL_BLACK);
    if(t == true) {
        fl_line_style(0, 4);
        fl_line(x1, y1, x2, y2);
        fl_line_style(0, 0);
    }
    
    else {
        fl_line(x1, y1, x2, y2);
    }
}

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
 * File:   square.cpp
 * Author: kinsey40
 * 
 * Created on 19 January 2018, 21:06
 * 
 * The source file for the Square class. Ideally, should have made two separate 
 * classes from this (a squares_answer; squares_pin), instead of using a flag 
 * to identify the objects that are answer squares. 
 */


#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include "square.h"


/** Constructor */
Square::Square(int x, int y, int w, int h, \
        int no_of_color_options, bool f, bool a)
    : Fl_Box(FL_UP_BOX, x, y, w, h, ""),
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


/** Inherits from the pre-made handle of Fl_Box, calls the colour function */
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


/** Show the value behind that square, by colouring it */
void Square::reveal(int data)
{
    no_of_clicks = data;
    colour();
}


/** Logically decide which colour the square should be, depending on 
 * no_of_clicks 
 */
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


/** Reveal for those squares that are an answer */
void Square::reveal_result(int data)
{
    v = data;
    set_answer_colour();
}


/** Colour the answer squares differently */
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
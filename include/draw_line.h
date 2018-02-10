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
 * File:   draw_line.h
 * Author: kinsey40
 *
 * Created on 16 January 2018, 21:47
 * 
 * The header file for the DrawLine class, which allows the user to draw a line
 * to the relevant FLTK window
 */


#ifndef DRAW_LINE_H
#define DRAW_LINE_H


#include <FL/Fl.H>
#include <FL/Fl_Widget.H>


/** DrawLine inherits from the Fl_Widget class */
class Draw_Line: public Fl_Widget {
public:
    /** Constructor */
    Draw_Line(int X, int Y, int X2, int Y2, bool thick, const char* L);
    
    /** Overloaded function */
    void draw();

private:
    /** Integer variables for the coordinates */
    int x1, y1, x2, y2;
    
    /** Bool to identify if this is a thick line or not */
    bool t;
};


#endif /* DRAW_LINE_H */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   draw_line.h
 * Author: kinsey40
 *
 * Created on 16 January 2018, 21:47
 */

#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>


class Draw_Line: public Fl_Widget {
public:
    Draw_Line(int X, int Y, int X2, int Y2, const char* L);
    void draw();

private:
    int x1, y1, x2, y2;
};


#endif /* DRAW_LINE_H */

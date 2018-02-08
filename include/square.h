/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   square.h
 * Author: kinsey40
 *
 * Created on 19 January 2018, 21:06
 */

#ifndef SQUARE_H
#define SQUARE_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>


class Square: public Fl_Box
{
public:
    Square(int x, int y, int w, int h, int no_of_color_options, bool f, bool a);
    int handle(int e);
    int get_number_of_clicks();
    void unfreeze();
    void freeze();
    void reveal(int data);
    void reveal_result(int data);
    int colour();
    int set_answer_colour();
    int clicks_guess();
    
    int no_of_clicks; 
    
private:
    int x_val, y_val;
    int no_colors;
    int v;
    
    const int width, height;
    
    bool frozen;
    bool answer;
    
};

#endif /* SQUARE_H */

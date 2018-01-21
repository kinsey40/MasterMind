/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   row.cpp
 * Author: kinsey40
 * 
 * Created on 17 January 2018, 21:02
 */

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <vector>
#include "row.h"
#include "square.h"


Row::Row(std::vector<int> data, int first_y_val, int first_x_val, int pin_width, int y_v)
:
data(data),
box_width(20),
box_height(20),
pin_dist(10),
first_y(first_y_val),
first_x(first_x_val),
y(y_v),
pin_w(pin_width)
{
    no_of_pins = data[0];
    no_of_colour_options = data[1];
    no_of_allowed_guesses = data[2];
    draw_boxes();
    
}


void Row::draw_boxes()
{
    int y_val = y + ((first_y - box_height) / 2);
    
    for(int i=0; i<no_of_pins; i++) {
        int x_val = (first_x + (pin_w*(i+1)) - ((pin_w + box_width) / 2));
        
        Square* sq = new Square(x_val, y_val, \
            box_width, box_height, no_of_colour_options, true);
        
        squares_vec.push_back(sq);
    }
}


void Row::unfreeze()
{
    for(int i=0; i<squares_vec.size(); i++){
        Square* sq = squares_vec[i];
        sq -> unfreeze();
    }
}


void Row::freeze()
{
    for(int i=0; i<squares_vec.size(); i++){
        Square* sq = squares_vec[i];
        sq -> freeze();
    }
}


std::vector<int> Row::get_guess()
{
    int g;
    guess.clear();
    
    for(int i=0; i<squares_vec.size(); i++){
        g = squares_vec[i]->get_number_of_clicks();
        guess.push_back(g);
    }
    
    return guess;
}
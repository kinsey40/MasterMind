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


Row::Row(std::vector<int> data)
:
data(data),
box_width(10),
box_height(10)
{
    no_of_pins = data[0];
    no_of_colour_options = data[1];
    no_of_allowed_guesses = data[2];
    draw_boxes();
    
}


void Row::draw_boxes()
{
    
    Square* sq = new Square(20, 40, box_width, box_height, no_of_colour_options, false);
    
}

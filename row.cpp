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


Row::Row(std::vector<int> data, int first_y_val, int first_x_val, int second_x_val, int pin_width, int y_v, int result_width, bool a_row)
:
data(data),
box_width(20),
box_height(20),
a_width(15),
a_height(15),
pin_dist(10),
first_y(first_y_val),
first_x(first_x_val),
second_x(second_x_val),
y(y_v),
pin_w(pin_width),
result_w(result_width)
{
    no_of_pins = data[0];
    no_of_colour_options = data[1];
    no_of_allowed_guesses = data[2];
    answer_row = a_row;
    draw_boxes();
    
}


void Row::draw_boxes()
{
    int y_val = y + ((first_y - box_height) / 2);
    int y_val_r = y + ((first_y - a_height) / 2);
    
    //int c_r = ((no_of_pins * result_w + 2 * second_x) / 2) + ((i+1) - (no_of_pins/2)) * a_width;
    
    for(int i=0; i<no_of_pins; i++) { 
        int x_val = (first_x + (pin_w*(i+1)) - ((pin_w + box_width) / 2));
        int x_val_r = (((no_of_pins * result_w) + (2 * second_x)) / 2) + (i - (no_of_pins/2)) * a_width;
        
        //int x_val_r = ((no_of_pins * result_w + 2 * second_x) / 2) + (a_width*(i+1));
        //int x_val_r = (second_x + (a_width*(i+1)));
        
        Square* sq = new Square(x_val, y_val, \
            box_width, box_height, no_of_colour_options, true, false);
        
        Square* sq_r = new Square(x_val_r, y_val_r, \
            a_width, a_height, no_of_colour_options, true, true);
        
        squares_vec.push_back(sq);
        results_vec.push_back(sq_r);
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


void Row::reveal(std::vector<int> answer_data)
{
    if(answer_row){
        for(int i=0; i<squares_vec.size(); i++){
            Square* sq = squares_vec[i];
            sq -> reveal(answer_data[i]);
        }
    }
}


void Row::reveal_result(std::vector<int> guess_data)
{
    for(int i=0; i<results_vec.size(); i++){
        Square* sq_r = results_vec[i];
        sq_r -> reveal_result(guess_data[i]);
    }
}
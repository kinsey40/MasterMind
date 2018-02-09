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
 * File:   row.cpp
 * Author: kinsey40
 * 
 * Created on 17 January 2018, 21:02
 * 
 * The source file for the Row class. Which couples various functions on the 
 * grouped square objects
 */


#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include "row.h"
#include "square.h"


/** Constructor */
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


/** Draw the actual answer boxes by calling the Square class, storing the objects
 * inside vectors.
 */
void Row::draw_boxes()
{
    int y_val = y + ((first_y - box_height) / 2);
    int y_val_r = y + ((first_y - a_height) / 2);
    
    for(int i=0; i<no_of_pins; i++) { 
        int x_val = (first_x + (pin_w*(i+1)) - ((pin_w + box_width) / 2));
        int x_val_r = (((no_of_pins * result_w) + (2 * second_x)) / 2) + (i - (no_of_pins/2)) * a_width;
        
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


/** Get the current input on the squares by the user, compare this to the answer
 * and send the result to the squares class to display the correct message
 */
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


/** Reveal the answer row at the end of the game */
void Row::reveal(std::vector<int> answer_data)
{
    if(answer_row){
        for(int i=0; i<squares_vec.size(); i++){
            Square* sq = squares_vec[i];
            sq -> reveal(answer_data[i]);
        }
    }
}


/** Reveal how correct the guess is by the user */
void Row::reveal_result(std::vector<int> guess_data)
{
    for(int i=0; i<results_vec.size(); i++){
        Square* sq_r = results_vec[i];
        sq_r -> reveal_result(guess_data[i]);
    }
}
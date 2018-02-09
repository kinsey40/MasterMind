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
 * File:   row.h
 * Author: kinsey40
 *
 * Created on 17 January 2018, 21:02
 * 
 * The header file for the Row class. 
 */


#ifndef ROW_H
#define ROW_H

#include <vector>
#include <FL/Fl.H>
#include "square.h"

/** The row class couples together several widgets, as each row is individual 
 * and should be treated as such 
 */
class Row
{
public:
    /** Constructor */
    Row(std::vector<int> data, int y_val, int first_x_val, int second_x_val, \
            int pin_width, int y_v, int result_width, bool a_row=false);
    
    /** Draw the normal and answer boxes, for answer boxes read in the guess as 
     * a vector */
    void draw_boxes();
    void draw_answer_boxes(std::vector<int> guess_in);
    
    /** The freezing and unfreezing functions allow to activate and deactivate 
     * the widgets via the use of flag in the Square class
     */
    void unfreeze();
    void freeze();
    
    /** Reveal the colours for the relevant numbers for the relevant squares */
    void reveal(std::vector<int> answer_data);
    void reveal_result(std::vector<int> guess_data);
    
    /** Return the guess, called by the Settings_Window class */
    std::vector<int> get_guess();
    
    
private:
    /** Integer values for placement, width, height (of widgets) and data 
     * values 
     */
    int no_of_pins;
    int no_of_allowed_guesses;
    int no_of_colour_options;
    int first_y;
    int first_x;
    int second_x;
    int pin_w;
    int result_w;
    int y;
    
    /* Flag for is this row is the answer row */
    bool answer_row;
    
    /** Constant integers for the square widths, heights and distances */
    const int box_width;
    const int box_height;
    const int a_width;
    const int a_height;
    const int pin_dist;
    
    /** Vectors to store the results and squares in order to call relevant 
     * freeze and unfreeze methods
     */
    std::vector<int> data;
    std::vector<int> guess;
    std::vector<Square*> squares_vec;
    std::vector<Square*> results_vec;
};


#endif /* ROW_H */

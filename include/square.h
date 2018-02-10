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
 * File:   square.h
 * Author: kinsey40
 *
 * Created on 19 January 2018, 21:06
 * 
 * Declares the Squares class, which is used to draw individual boxes to 
 * represent the MasterMind pins
 */


#ifndef SQUARE_H
#define SQUARE_H


#include <FL/Fl.H>
#include <FL/Fl_Box.H>


/** Inherits from the Fl_Box class */
class Square: public Fl_Box
{
public:
    /** Constructor */
    Square(int x, int y, int w, int h, int no_of_color_options, bool f, bool a);
    
    /** Handle is an overloaded function, it handles the click event */
    int handle(int e);
    
    /** Functions to grab the number_of_clicks variable and set the relevant 
     * colour 
     */
    int get_number_of_clicks();
    int colour();
    int set_answer_colour();
    int clicks_guess();
    
    /** Freezing and unfreezing, need to have the squares as 'inactive' or 
     * 'active' at specific points within the applications process 
     */
    void unfreeze();
    void freeze();
    void reveal(int data);
    void reveal_result(int data);

    
private:
    /** Integer variables, easy access for each individual object */
    int x_val, y_val;
    int no_colors;
    int v;
    int no_of_clicks;
    
    /** Keep the width and height of the squares constant */
    const int width, height;
    
    /** Whether this is an 'answer' square, i.e. where the result is displayed*/
    bool answer;
    
    /** Whether the square is currently  'frozen' and therefore inactive */
    bool frozen;
};

#endif /* SQUARE_H */

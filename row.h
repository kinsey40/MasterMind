/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   row.h
 * Author: kinsey40
 *
 * Created on 17 January 2018, 21:02
 */

#ifndef ROW_H
#define ROW_H

#include <vector>
#include <FL/Fl.H>

#include "square.h"


class Row
{
public:
    Row(std::vector<int> data, int y_val, int first_x_val, int second_x_val, int pin_width, int y_v, int result_width, bool a_row=false);
    void draw_boxes();
    void draw_answer_boxes(std::vector<int> guess_in);
    void unfreeze();
    void freeze();
    void reveal(std::vector<int> answer_data);
    void reveal_result(std::vector<int> guess_data);
    std::vector<int> get_guess();
    
    
private:
    int no_of_pins;
    int no_of_allowed_guesses;
    int no_of_colour_options;
    int first_y;
    int first_x;
    int second_x;
    int pin_w;
    int result_w;
    int y;
    
    bool answer_row;
    
    const int box_width;
    const int box_height;
    const int a_width;
    const int a_height;
    const int pin_dist;
    
    std::vector<int> data;
    std::vector<int> guess;
    std::vector<Square*> squares_vec;
    std::vector<Square*> results_vec;
};


#endif /* ROW_H */

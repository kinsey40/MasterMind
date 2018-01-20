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


class Row
{
public:
    Row(std::vector<int> data);
    void draw_boxes();
    void cover();
    
    
private:
    int no_of_pins;
    int no_of_allowed_guesses;
    int no_of_colour_options;
    
    const int box_width;
    const int box_height;
    
    std::vector<int> data;
    std::vector<int> answer;
};


#endif /* ROW_H */

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
 * File:   game_window.h
 * Author: kinsey40
 *
 * Created on 10 January 2018, 22:52
 * 
 * The header file which declares the Game_Window class, the relevant functions 
 * and variables
 */


#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H


#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>
#include "draw_line.h"
#include "settings_window.h"
#include "row.h"


/** Game_Window inherits from the Fl_Double_Window, the Fl_Double_Window is used
 * as this window implements a lot of graphical widgets
 */
class Game_Window: public Fl_Double_Window
{
public:
    /** Constructor */
    Game_Window(int w, int h, const char* n);
        
    /** Show and hide windows allow control from Settings_Window class */
    void show_window(std::vector<int> data);
    void hide_window();
    
    /** Add lines to make the window look a lot neater */
    void add_vertical_lines();
    void add_horizontal_lines();
    
    /** Draws the guess number widgets on the left hand side of the window */
    void draw_numbers();
    
    /** Adds the row objects and the other button widgets on the window */
    void add_rows();
    void add_other_buttons();
    
    /** Advance the row forward in order to unfreeze the next row */
    void advance_row();
    
    /** Generate an answer randomly */
    void generate_answer();
    
    /** Act in case of game win and game lost */
    void game_win();
    void game_lost();
    
    /** Call this function when the reset button is clicked */
    void reset_win();
    
    /** Get and evaluate the guess, returning a bool to show if game is over */
    bool get_guess();
    bool evaluate_guess();
    
    /** Get the relevant values (constants)*/
    int get_pin_width() const;
    int get_result_width() const;
    
    /** All the widget callbacks */
    static void check_but_cb(Fl_Widget* obj, Game_Window* win);
    static void win_cb(Fl_Widget* obj, Game_Window* win);
    static void c_settings_but_cb(Fl_Widget* obj, Game_Window* win);
    static void quit_but_cb(Fl_Widget* obj, Game_Window* win);
    static void reset_but_cb(Fl_Widget* obj, Game_Window* win);
    
    
private:
    int width;
    int height;
    int no_of_pins;
    int no_of_allowed_guesses;
    int no_of_colour_options;
    int second_x_coord;
    int second_y_coord;
    int third_x_coord;
    int third_y_coord;
    int y_coord;
    int current_row;
    int right_place;
    int wrong_place;
    int g_count;
    int a_count;
    
    /** Constant integers for the X, Y values of the widgets */
    const int first_x_coord;
    const int first_y_coord;
    const int pin_width;
    const int o_but_width;
    const int o_but_height;
    const int result_width;
    
    /** Whether the game has ended, act appropriately */
    bool game_end;
    
    /** Prevents more than one Game_Window being opened */
    static bool window_already_open;
    
    const char* name;
    
    /** Vectors for all the guess, answers and encoding of the answer 
     * evaluation
     */
    std::vector<int> d;
    std::vector<int> current_guess;
    std::vector<int> answers;
    std::vector<int> incorrect_guess_places;
    std::vector<int> incorrect_answer_places;
    std::vector<int> passing_guess;
    
    /** Store these widgets in vectors to access them and delete them */
    std::vector<Draw_Line*> lines;
    std::vector<Row*> rows_vec;
    
    /** The FLTK widget declarations */
    Fl_Button* reset_but;
    Fl_Button* quit_but;
    Fl_Button* c_settings_but;
    Fl_Button* check_but;
    Fl_Window* end_win;
};

#endif /* GAME_WINDOW_H */
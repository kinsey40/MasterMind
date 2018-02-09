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
 * File:   game_window.cpp
 * Author: kinsey40
 * 
 * Created on 10 January 2018, 22:52
 * 
 * The source file for the Game_Window class. Here the main functions that 
 * control the games functionality are defined. 
 */


#include <vector>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include "game_window.h"
#include "settings_window.h"


/** Global variable controls only having one Game_Window open */
bool Game_Window::window_already_open = false;


/** Constructor */
Game_Window::Game_Window(int w, int h, const char* n)
    : Fl_Double_Window(w, h, n),
      width(w),
      height(h),
      name(n),
      pin_width(100),
      result_width(30),
      first_x_coord(30),
      first_y_coord(50),
      o_but_width(80),
      o_but_height(30)
{
}


/** Show the window and set the relevant parameters */
void Game_Window::show_window(std::vector<int> data)
{   
    std::srand(time(NULL));

    if(window_already_open == false){
        d.clear();
        d = data;
        no_of_pins = data[0];
        no_of_colour_options = data[1];
        no_of_allowed_guesses = data[2];
    
        window_already_open = true;
        current_row = 0;
        game_end = false;
    
        this->begin();

        generate_answer();
        add_vertical_lines();
        add_horizontal_lines();
        draw_numbers();
        add_rows();
        add_other_buttons();

        this->callback((Fl_Callback*) win_cb, this);
        this->end();
        this->show();

    }
}


/** Hide the window, allows user to close Game_Window from Settings_Window */
void Game_Window::hide_window()
{
    if(end_win != NULL){
        end_win->hide();
    }
    
    this->hide();
    window_already_open = false;
}


void Game_Window::add_vertical_lines()
{   
    second_x_coord = (no_of_pins * get_pin_width() + first_x_coord);
    second_y_coord = first_y_coord * (no_of_allowed_guesses + 2);
    third_x_coord = second_x_coord + (no_of_pins * get_result_width());
    
    Draw_Line* v_line_1 = new Draw_Line(first_x_coord, first_y_coord, \
            first_x_coord, second_y_coord, NULL);
    Draw_Line* v_line_2 = new Draw_Line(second_x_coord, first_y_coord, \
            second_x_coord, second_y_coord, NULL);
    Draw_Line* v_line_3 = new Draw_Line(third_x_coord, first_y_coord, \
            third_x_coord, second_y_coord, NULL);
    
    lines.push_back(v_line_1);
    lines.push_back(v_line_2);
    lines.push_back(v_line_3);
    
}


void Game_Window::add_horizontal_lines()
{
    for(int i=0; i<=(no_of_allowed_guesses + 1); i++) {
        y_coord = first_y_coord * (i+1);
        Draw_Line* line = new Draw_Line(first_x_coord, y_coord, \
            third_x_coord, y_coord, NULL);
        lines.push_back(line);
    }
    
}


int Game_Window::get_pin_width() const 
{
    return pin_width;
}


int Game_Window::get_result_width() const
{
    return result_width;
}


/** Draw the numbers down the left hand side of the Game_Window, difficulty
 * arose directly inserting the const char * value into the Fl_box, this appears
 * to be a slight bug with FLTK. Therefore, the switch-case statement is 
 * required 
 */
void Game_Window::draw_numbers()
{
    for(int i=0; i<=no_of_allowed_guesses; i++){
        const char* input;
        int x = i + 1;
        
        if(i == no_of_allowed_guesses) {
            input = "Ans";
        }
        else {
            switch(x) {
                case 1:
                    input = "1.";
                    break;
                case 2:
                    input = "2.";
                    break;
                case 3:
                    input = "3.";
                    break;
                case 4:
                    input = "4.";
                    break;
                case 5:
                    input = "5.";
                    break;
                case 6:
                    input = "6.";
                    break;
                case 7:
                    input = "7.";
                    break;
                case 8:
                    input = "8.";
                    break;
                case 9:
                    input = "9.";
                    break;
                case 10:
                    input = "10.";
                    break;
                default:
                    input="N/A";
            }
        }
        Fl_Box* b = new Fl_Box(2, ((i+1)*first_y_coord), (first_x_coord - 5), \
                first_y_coord, input);
        b->box(FL_FLAT_BOX);
    }
}


/** Create the Rows objects, store these objects into a vector to interact with 
 * later
 */
void Game_Window::add_rows()
{
    for(int i=0; i<=no_of_allowed_guesses; i++){
        int y_val = (i+1)*first_y_coord;
        Row* obj;
        
        if(i == no_of_allowed_guesses) {
            obj = new Row(d, first_y_coord, first_x_coord, second_x_coord, \
                    pin_width, y_val, result_width, true);
        }
        else {
            obj = new Row(d, first_y_coord, first_x_coord, second_x_coord, \
                    pin_width, y_val, result_width);
        }
        
        rows_vec.push_back(obj);
    }
    
    rows_vec[current_row] -> unfreeze();
}


/** Advance the row, by freezing the current row to prevent interaction and 
 * unfreezing the next row, to allow interactions 
 */
void Game_Window::advance_row()
{
    rows_vec[current_row] -> freeze();
    current_row++;
    rows_vec[current_row] -> unfreeze();
}


/** Get the current guess and evaluate if the game is complete */
bool Game_Window::get_guess()
{
    current_guess = rows_vec[current_row] -> get_guess();
    bool incomplete = false;
    int checker = 0;
    
    for(int i=0; i<current_guess.size(); i++){
        checker = current_guess[i];
        if(checker == 0){
            incomplete = true;
            break;
        }
    }
    
    return incomplete;
}


/** Add the other buttons to the window with relevant callbacks and positions */
void Game_Window::add_other_buttons()
{
    int check_x_coord = (second_x_coord + first_x_coord - o_but_width) / 2; 
    int check_y_coord = first_y_coord * (no_of_allowed_guesses + 2) + 10;
    
    int reset_x_coord = first_x_coord;
    int reset_y_coord = 10;
   
    int quit_x_coord = this->w() - first_x_coord - o_but_width;
    int quit_y_coord = 10;
    
    int c_settings_x_coord = ((quit_x_coord + \
            (reset_x_coord + o_but_width)) / 2) - o_but_width;
    int c_settings_y_coord = 10 ;
    
    check_but = new Fl_Button(check_x_coord, check_y_coord, o_but_width, \
            o_but_height, "Check");
    check_but -> callback((Fl_Callback*) check_but_cb, this);
    this->add(check_but);
    
    reset_but = new Fl_Button(reset_x_coord, reset_y_coord, o_but_width, \
            o_but_height, "Reset");
    reset_but -> callback((Fl_Callback*) reset_but_cb, this);
    this->add(reset_but);
    
    quit_but = new Fl_Button(quit_x_coord, quit_y_coord, o_but_width, \
            o_but_height, "Quit");
    quit_but -> callback((Fl_Callback*) quit_but_cb, this);
    this->add(quit_but);
    
    c_settings_but = new Fl_Button(c_settings_x_coord, c_settings_y_coord, \
            o_but_width*2, o_but_height, "Change Settings");
    c_settings_but -> callback((Fl_Callback*) c_settings_but_cb, this);
    this->add(c_settings_but);
}


/** Callback for the 'check' button */
void Game_Window::check_but_cb(Fl_Widget* obj, Game_Window* win)
{
    bool incom;
    incom = win->get_guess();
    
    if(incom == false){
        bool g_over = win->evaluate_guess();
        if(g_over == false) win->advance_row();
    }
}


/** Callback for the 'reset' button */
void Game_Window::reset_but_cb(Fl_Widget* obj, Game_Window* win)
{
    win->reset_win();
}


/** Cast the Settings_Window class onto the Fl::first_window() parameter in 
 * order to call the function which re-launches the game 
 */
void Game_Window::reset_win()
{
    if(end_win != NULL){
        end_win->hide();
    }
    
    this->hide();
    Settings_Window* upper_win = (Settings_Window*) Fl::first_window();
    
    window_already_open = false;
    upper_win -> launch_game();
    
}


/** Callback for the Quit button, uses the Fl::next_window() to grab the 
 * Settings_Window, whilst passing the address of the Game_Window 
 */
void Game_Window::quit_but_cb(Fl_Widget* obj, Game_Window* win)
{ 
    if(win->end_win != NULL){
        win->end_win->hide();
    }
    
    Settings_Window* w = (Settings_Window*) Fl::next_window(Fl::first_window());
    w->close_all();
}


/** Change Settings by merely closing the Game_Window, and re-setting the 
 * only-one-window flag
 */
void Game_Window::c_settings_but_cb(Fl_Widget* obj, Game_Window* win)
{
    if(win->end_win != NULL){
        win->end_win->hide();
    }
    
    window_already_open = false;
    win->hide();
}


/** Generate a random answer using basic random number generator */
void Game_Window::generate_answer()
{
    answers.clear();
    for(int i=0; i < no_of_pins; i++){
        answers.push_back((rand() % no_of_colour_options) + 1);
    }
}


/* Evaluate the guess, by comparing the guess and answer vectors. Firstly, look
 * at all the values that are both correct and in the correct place. Next, 
 * search both vectors looking for numbers that are equal. 
 * 
 * Count how many of these numbers are equal in the vectors for a particular 
 * value, then use the smaller amount, as per the game for MasterMind
 */
bool Game_Window::evaluate_guess()
{
    right_place = 0;
    wrong_place = 0;

    incorrect_guess_places.clear();
    incorrect_answer_places.clear();
    passing_guess.clear();
    
    assert(no_of_pins == current_guess.size());
    assert(no_of_pins == answers.size());

    for(int j=0; j < no_of_pins; j++) {
        if(answers[j] == current_guess[j]) {
            right_place += 1;
        }
        else {
            incorrect_guess_places.push_back(current_guess[j]);
            incorrect_answer_places.push_back(answers[j]);
        }
    }
    
    for(int j=1; j < (no_of_colour_options + 1); j++) {
        g_count = 0;
        a_count = 0;

        g_count = std::count(incorrect_guess_places.begin(), \
                incorrect_guess_places.end(), j);
        a_count = std::count(incorrect_answer_places.begin(), \
                incorrect_answer_places.end(), j);

        if(a_count > 0) {
            if(g_count <= a_count) {
                wrong_place += g_count;
            }
            else {
                wrong_place += a_count;
            }
        }
    }
    
    for(int i=0; i < right_place; i++) {
        passing_guess.push_back(1);
    }
    
    for(int i=0; i < wrong_place; i++) {
        passing_guess.push_back(0);
    }
    
    for(int i=0; i < no_of_pins - (right_place + wrong_place); i++) {
        passing_guess.push_back(-1);
    }
    
    rows_vec[current_row] -> reveal_result(passing_guess);
    bool game_over = true;
    
    if(right_place == no_of_pins) {
        game_win();
    }
    else if(current_row >= no_of_allowed_guesses-1) {
        game_lost();
    }
    else {
        game_over = false;
    }

    return game_over;
}


/** Create a new window if the game has been won, and display a nice message */
void Game_Window::game_win()
{
    if(game_end == false) {
        end_win = new Fl_Window(250, 100, "game over");
    
        Fl_Box* end_message = new Fl_Box(10, 10, 230, 80, "You Win!");
        end_message->box(FL_NO_BOX);
        end_message->labelsize(42);
        end_message->labelfont(FL_BOLD);

        end_win->add(end_message);

        for(int i=0; i<no_of_allowed_guesses; i++) {
            rows_vec[i] -> freeze();    
        }
        rows_vec[no_of_allowed_guesses] -> reveal(answers);

        end_win->show();
    }
    
    game_end = true;
}


/** Create a new window if the game has been lost, and display a nice message */
void Game_Window::game_lost()
{
    if(game_end == false) {
        end_win = new Fl_Window(250, 100, "game over");
        
        Fl_Box* end_message = new Fl_Box(10, 10, 230, 80, "You Lost!");
        end_message->box(FL_NO_BOX);
        end_message->labelsize(42);
        end_message->labelfont(FL_BOLD);
        
        end_win->add(end_message);

        for(int i=0; i<no_of_allowed_guesses; i++){
            rows_vec[i] -> freeze();    
        }
        rows_vec[no_of_allowed_guesses] -> reveal(answers);

        end_win->show();
    }
    
    game_end == true;
}


/** This allows the user to appropriately hide the window and re-set the flag */
void Game_Window::win_cb(Fl_Widget* obj, Game_Window* win)
{
    window_already_open = false;
    win->hide();
}

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
 * File:   settings_window.cpp
 * Author: kinsey40
 * 
 * Created on 10 January 2018, 22:22
 * 
 * The Settings_Window cpp file, defining the relevant functions for this class
 */


#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_JPEG_Image.H>
#include "settings_window.h"
#include "game_window.h"


/** Constructor */
Settings_Window::Settings_Window(int w, int h, const char* n)
: 
Fl_Window(w, h, n),
width(w),
height(h),
name(n)
{
    set_starting_values();
    
    this->callback((Fl_Callback*) win_cb, this);
    this->begin();
    this->end();
    populate_window();
    this->show();
}


/** Sets the starting values as default */
void Settings_Window::set_starting_values()
{
    no_instruction_wins = 0;
    no_of_pins = 4;
    no_of_allowed_guesses = 10;
    no_of_colour_options = 4;
    game_window_open = false;
}


/** Populates the data vector */
void Settings_Window::populate_data()
{
    data.clear();
    data.push_back(no_of_pins);
    data.push_back(no_of_colour_options);
    data.push_back(no_of_allowed_guesses);
}


void Settings_Window::set_game_window_open()
{
    if(game_window_open == true) { 
        game_window_open = false;
    }

    else { 
        game_window_open = true;
    }
}


/** Populates the window with the widgets, assigns relevant values for the X, Y,
 * width and height values for those widgets. It also sets the callbacks for 
 * those widgets.
 */
void Settings_Window::populate_window()
{   
    int but_width = 80;
    int but_height = 50;
    
    int width = (this->w() / 2) - (but_width / 2);
    int height = 250;
    
    int l_width = 80;
    int l_height = 20;
    
    int l_gap = 15;
    
    int m_width = 200;
    int m_height = 70;
    int m_x_val = (this->w() / 2) - (m_width / 2);
    int m_y_val = 10;
    
    int i_width = 105;
    int i_height = 25;
    int i_x_val = (this->w() / 2) - (i_width / 2);
    int i_y_val = 100;
    
    int x_value = (this->w() / 2) - (l_width / 2);
    
    int first_y_val = 140;
    int second_y_val = first_y_val + (1 * (l_height + l_gap));
    int third_y_val = first_y_val + (2 * (l_height + l_gap));
    
    message = new Fl_Box(m_x_val, m_y_val, m_width, m_height, "Welcome to\nMasterMind");
    message->box(FL_NO_BOX);
    message->labelsize(30);
    message->labelfont(FL_BOLD);
    
    instructions = new Fl_Button(i_x_val, i_y_val, i_width, i_height, "Instructions");
    instructions->labelsize(14);
    instructions->labelcolor(FL_BLUE);
    instructions->labelfont(FL_BOLD);
    instructions->callback((Fl_Callback*) instructions_cb, this);
    
    but = new Fl_Button(width, height, but_width, but_height, "Launch");
    but -> callback((Fl_Callback*) launch_cb, this);
    
    label_no_of_pins = new Fl_Choice(x_value, first_y_val, l_width, l_height, "No. of pins:");
    label_no_of_pins->add("3", 0, (Fl_Callback*) no_of_pins_3_cb, this, 0);
    label_no_of_pins->add("4", 0, (Fl_Callback*) no_of_pins_4_cb, this, 0);
    label_no_of_pins->add("5", 0, (Fl_Callback*) no_of_pins_5_cb, this, 0);
    
    label_no_of_allowed_guesses = new Fl_Choice(x_value, second_y_val, l_width, l_height, "No. of guesses:");
    label_no_of_allowed_guesses->add("8", 0, (Fl_Callback*) no_of_allowed_guesses_8_cb, this, 0);
    label_no_of_allowed_guesses->add("9", 0, (Fl_Callback*) no_of_allowed_guesses_9_cb, this, 0);
    label_no_of_allowed_guesses->add("10", 0, (Fl_Callback*) no_of_allowed_guesses_10_cb, this, 0);
    
    label_no_of_colours = new Fl_Choice(x_value, third_y_val, l_width, l_height, "No. of colours:");
    label_no_of_colours->add("3", 0, (Fl_Callback*) no_of_colours_3_cb, this, 0);
    label_no_of_colours->add("4", 0, (Fl_Callback*) no_of_colours_4_cb, this, 0);
    label_no_of_colours->add("5", 0, (Fl_Callback*) no_of_colours_5_cb, this, 0);
    
    label_no_of_pins->value(1);
    label_no_of_allowed_guesses->value(2);
    label_no_of_colours->value(1);
    
    this->add(message);
    this->add(instructions);
    this->add(but);
    this->add(label_no_of_pins);
    this->add(label_no_of_allowed_guesses);
    this->add(label_no_of_colours);
}


/** Calls the launch game function, as the launch button callback */
void Settings_Window::launch_cb(Fl_Widget* obj, Settings_Window* win)
{   
    win->launch_game();
}


/** Launches the applications game window by defining the Game_Window game */
void Settings_Window::launch_game()
{
    populate_data();
    int w = 150 * no_of_pins;
    int h = (50 * no_of_allowed_guesses) + 150;
    
    if(game_window_open == false) {
        set_game_window_open();
        Game_Window* game = new Game_Window(w, h, "Game");
        game->show_window(data);
    }
}


/** The callback for the actual window (the Settings_Window object itself) */
void Settings_Window::win_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->close_all();
}


void Settings_Window::no_of_pins_3_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_pins = 3;
}


void Settings_Window::no_of_pins_4_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_pins = 4;
}


void Settings_Window::no_of_pins_5_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_pins = 5;
}


void Settings_Window::no_of_allowed_guesses_8_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_allowed_guesses = 8;
}


void Settings_Window::no_of_allowed_guesses_9_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_allowed_guesses = 9;
}


void Settings_Window::no_of_allowed_guesses_10_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_allowed_guesses = 10;
}


void Settings_Window::no_of_colours_3_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_colour_options = 3;
}


void Settings_Window::no_of_colours_4_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_colour_options = 4;
}


void Settings_Window::no_of_colours_5_cb(Fl_Widget* obj, Settings_Window* win)
{
    win->no_of_colour_options = 5;
}


/** Callback for the instructions button */
void Settings_Window::instructions_cb(Fl_Widget* obj, Settings_Window* win)
{
    int value = win->no_instruction_wins;
    int win_size = 500;
    int x_gap = 10;
    int y_top_gap = 10;
    int y_gap = 300;
    
    Fl_JPEG_Image* p = new Fl_JPEG_Image("resources/game_image.jpg");
    
    if(value == 0){
        win->new_win = new Fl_Window(win_size, win_size, "instructions");
        Fl_Multiline_Output *o = new Fl_Multiline_Output((x_gap/2), \
                (y_top_gap/2), win->new_win->w()-x_gap, \
                win->new_win->h()-y_gap);
        o->wrap(1);
        o->value(
        "Choose the settings on the settings screen"
        "and hit the launch button when ready. The following screen will appear,"
        " click on the square boxes to input a guess, the result is displayed on"
        " the right of the screen. \n\n To input a guess, click the boxes, then "
        " click the 'check' button. A white box indicates a correct place, a "
        " black square indicates a wrong place, but correct colour.\n\n The image "
        " below shows the game in flow, it should be straightforward to "
        " understand. The answer will be displayed upon game ending at the "
        " bottom of the window."
        );
        
        Fl_Box* image_box = new Fl_Box((x_gap/2), win->new_win->h()-y_gap, \
                win->new_win->w()-x_gap, (y_gap - y_top_gap));
        
        image_box->image(p);
        image_box->redraw();
        
        win->new_win->callback((Fl_Callback*) win_i_cb, win);
        win->new_win->add(image_box);
        win->new_win->add(o);
        win->new_win->show();
    }
    
    win->no_instruction_wins++;
}


/** Callback for the created instructions window */
void Settings_Window::win_i_cb(Fl_Widget* obj, Settings_Window* win)
{
    Fl_Window* i_win = (Fl_Window*) obj;
    Fl::delete_widget(i_win);

    win->no_instruction_wins = 0;
}


/** Appropriately close all the currently open FLTK windows */
void Settings_Window::close_all()
{
    if(game_window_open == true){
      Fl::delete_widget(Fl::next_window(Fl::first_window()));  
    }
    if(no_instruction_wins != 0){
        Fl::delete_widget(new_win);
    }
    Fl::delete_widget(this);
}
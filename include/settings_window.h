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
 * File:   settings_window.h
 * Author: kinsey40
 *
 * Created on 10 January 2018, 22:22
 * 
 * The Settings_Window header file, defines the Settings_Window class and 
 * associated functions and variables for that class.
 */

#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H


#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include "game_window.h"


/** The Settings_Window class inherits from the Fl_Window class. This means that
 * it inherently creates the actual window. The populate_window function allows
 * for the window to be populated with various different widgets. A lot of these
 * have associated, relevant callbacks.
 * 
 * It is to be used to create a Settings_Window object i.e:
 * Settings_Window* win = obj(300, 300, "settings");
*/
class Settings_Window: public Fl_Window
{
public:
    Settings_Window(int w, int h, const char* n);
    
    /** Set the default values for the game */
    void set_starting_values();
    void set_game_window_open();
    
    /** Populate the window and the data vector */
    void populate_window();
    void populate_data();
    
    /** Launch the actual game */
    void launch_game();
    
    /** Close everything in the correct manner */
    void close_all();
    
    /** Callbacks for the number of pins menu options */
    static void no_of_pins_3_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_pins_4_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_pins_5_cb(Fl_Widget* obj, Settings_Window* win);
    
    /** Callbacks for the number of allowed guesses menu options */
    static void no_of_allowed_guesses_8_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_allowed_guesses_9_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_allowed_guesses_10_cb(Fl_Widget* obj, Settings_Window* win);
    
    /** Callbacks for the number of colours menu options */
    static void no_of_colours_3_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_colours_4_cb(Fl_Widget* obj, Settings_Window* win);
    static void no_of_colours_5_cb(Fl_Widget* obj, Settings_Window* win);
    
    /** Callback for the instructions button */
    static void instructions_cb(Fl_Widget* obj, Settings_Window* win);
    
    /** Callback for the opened instructions window */
    static void win_i_cb(Fl_Widget* obj, Settings_Window* win);
    
    /** Callback for the launch button */
    static void launch_cb(Fl_Widget* obj, Settings_Window* win);
    
    /** Callback for window */
    static void win_cb(Fl_Widget* obj, Settings_Window* win);
    
    
private:
    /** Constant integers for the width and height of the window */
    const int width;
    const int height;
    
    /** Constant for the name of the window */
    const char* name;
    
    bool game_window_open;
    
    /** Relevant integer values for the various game parameters */
    int no_of_pins;
    int no_of_allowed_guesses;
    int no_of_colour_options;
    int no_instruction_wins;
    
    /** Integer vector to hold the above values, to pass to game_window */
    std::vector<int> data;
    
    /** Various FL_Widgets defined here */
    Fl_Box* message;
    Fl_Button* instructions;
    Fl_Button* but;
    Fl_Choice* label_no_of_pins;
    Fl_Choice* label_no_of_allowed_guesses;
    Fl_Choice* label_no_of_colours;
    Fl_Window* new_win;
};

#endif /* SETTINGS_WINDOW_H */
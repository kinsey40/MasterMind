# MasterMind
MasterMind, made in C++ using FLTK 1.3.4 as the GUI. Netbeans was used as the IDE. 

# Setup
If you would to just like to run the application, see the Debug and Release versions in the dist folder. Note that these will only work for linux machines, if you are using a different OS, you'll need to build the application on your machine. After cloning this repository, just run the application and follow the in-game instructions. 

If instead, you'd like to clone to the repository to build and compile the actual code, then you'll need to ensure that you install the FLTK 1.3.4 library which can be found [here](http://www.fltk.org/index.php). See the FLTK set-up instructions for details about how to install this library (it follows the same format of most C++ external libraries (configure -> make -> make install -> clean). 

To build the project, I created a binary file using the MagikImage software (available on most linux distros), which was named game_image.h - this file needs to be included in the main.cpp file. The program should subsequently work appropriately if this is completed.  

If you have any problems with the set-up process, than please message or e-mail me. 

# Known Issues
Currently, causing the game to 'reset' causes a warning to arise in the terminal (Bad Drawable). Currently, I believe this may potentially arise from the interaction between the OS and the FLTK library, rather than a bug in the code. However, I may be mistaken, I would be extremely grateful if anyone could solve/explain this issue. 

A further issue is that currently, the squares class has a flag which tells the application whether the FL_Box object being drawn is a 'guess output' or 'user input'. Ideally, I should have created 2 seperate derived classes from this class, with overloaded functions, for the input guesses and outputted results. 

If anyone has any suggestions for additional features or wants to imrpove/add to the code then feel free to submit a pull request.

# Comments
I don't have a great deal of experience with C++, so any improvements regarding the code are greatly appreciated and welcomed! I found the FLTK GUI to be quite clunky and not particularly well documented. The simplicity of it's graphics and speed are a big benefit though. I would however, like to extend my thanks and appreciation to the FLTK team, for developing and maintaining this library. 




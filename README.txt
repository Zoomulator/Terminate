#########################################################
libTerminate is distributed under the Zlib/libPNG license
Copyright (c) 2013 Kim Simmons
#########################################################


1. Dependencies
Written in C++11 using CMake as build system
For instant satisfaction, SDL1.2 and SDL_image is required
but is easily replaceable. The dependence is put in a
separate library. However the demos requires SDL to compile.


2. What is Terminate?
A simple terminal emulator for typing characters to the
a screen. It doesn't handle input, all it does is display
output. Created with SDL in mind but allows easy
integration with other systems/libraries by overloading
the provided Context class. Ideal for colorful ASCII art, 
roguelikes and general nostalgia for the good ol day's
with greenscreens and punchcards.


3. Features
* 8bit charmap loading (indexed png)
* Two 24bit colors per character: Background and fontcolor
* Easy typing onto buffers with the TTY class acting as cursor.
* TTY typing with insert, scroll and wrap
* Copy character buffers onto others with position and size.


4. Why Terminate?
I wanted a simple way of writing to a half decent terminal
to produce quick outputs that required a bit more than the
usual stdout could provide. There's the usual NCurses for
unix systems, but I wanted something that was easier to
get onto Windows as well. PDCurses is that natural choice,
but I found it icky. It's quite aged and isn't really
capable of providing a truly cross compatible terminal for
more advaced cursing. Unfortunately there were some dependency
issues with their SDL port PDCurses on some linuxes which 
finally made me decide to roll my own terminal-ish library.

5. And the name?
Terminal.. simulate.. Terminate!


6. Possible further development
Multiple charmaps
TTF support
More rendering contexts like OpenGL, SFML and so on
UI utilities like windows, panels, labels..

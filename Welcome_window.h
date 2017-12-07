//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//Welcome_window.h

#include "lib/Window.h"
#include "lib/Graph.h"
#include "lib/GUI.h"
using namespace Graph_lib;

//The first window the user sees, with an attractive (if somewhat slow to load) background image and
//some fancy buttons.  Also give info about the team members and instructions for playing the game
class Welcome_window : public Graph_lib::Window{
private:
	Image pancakeback;
	Button next_button;
	Button quit_button;
	bool chose_quit = true;//whether to exit program when window closes
	
public:
	Welcome_window(Point, int, int, const String&);
	void quit();
	void next();
	bool pressed_quit() const { return chose_quit; }//called by main.cpp to determine whether to quit
};
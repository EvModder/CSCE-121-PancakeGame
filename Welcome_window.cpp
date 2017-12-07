//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//Welcome_window.cpp

#include "Welcome_window.h"

//constructor, attaches background and buttons to the window
Welcome_window::Welcome_window(Point xy, int w, int h, const String& title)
:	Window(xy,w,h,title),
	next_button{Point{330,10},310,100,"Play Now",
			[](Address,Address pw){reference_to<Welcome_window>(pw).next();}},
		quit_button{Point{x_max()-200,y_max()-100},200,100,"Quit",					
			[](Address,Address pw){reference_to<Welcome_window>(pw).quit();}}, 
		pancakeback{Point {0,0}, "back.jpg"}
{
	attach(pancakeback); 
	attach(next_button);
	attach(quit_button);
}

//quit the game
void Welcome_window::quit(){
	hide();
}
//continue to the next part of the game
void Welcome_window::next(){
	chose_quit = false;
	hide();
}
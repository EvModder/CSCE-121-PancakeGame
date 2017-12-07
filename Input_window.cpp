//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//Input_window.cpp

#include "Input_window.h"

//constructor for the input window, creates & attaches buttons and highscores
Input_window::Input_window(Point tl, int w, int h, const string& title, int max_difficulty, vector<string> scores)
: Window(tl,w,h,title), initials_input(Point(w/2-30,1),60,20,"Initials:"),
 next_button(Point(w-80,0),80,20,"Continue",[](Address, Address pw){reference_to<Input_window>(pw).next();}),
 quit_button(Point(w-160,0),80,20,"Quit Game",[](Address, Address pw){reference_to<Input_window>(pw).quit();}),
 difficulty_label(Point(0,0),100,30,"Selected: "+max_difficulty),
 highscores_box(Point(200,100),w-300,h-200),
 scores_text(5)//size=5, displays the 5 highscores
{
	highscores_box.set_fill_color(Color::white);
	attach(highscores_box);
	for(int i=0; i<scores_text.size() && i<scores.size(); ++i){
		scores_text[i] = new Text(Point(highscores_box.point(0).x+20,highscores_box.point(0).y+20*(i+1)),scores[i]);
		attach(*scores_text[i]);
	}
	attach(next_button);
	attach(quit_button);
	attach(initials_input);
	attach(difficulty_label);
	
	for(int i=0; i<max_difficulty-1; ++i){
		difficulty_buttons.push_back(new Button(Point(0,(i+1)*31),100,30,"Difficulty "+to_string(i+2),
		[](Address pwidget, Address pwindow){reference_to<Input_window>(pwindow).pick_difficulty(pwidget);}));
		attach(*difficulty_buttons[i]);
	}
}

//destructor to clean up some pointer stuff
Input_window::~Input_window(){
	for(auto k : difficulty_buttons)
		delete k;
	for(auto k : scores_text)
		delete k;
}
//quit the game
void Input_window::quit(){
	hide();
}
//continue to the next part of the game
void Input_window::next(){
	chose_quit = false;
	hide();
}
//called when the player hits a difficulty button, selects the game's difficulty level
void Input_window::pick_difficulty(Address widget){
	//widget cast, http://piazza.com/class/ie0frma5qre572?cid=320
	string label = static_cast<Fl_Widget*>(widget)->label();
	istringstream iss(label);
	iss >> label >> difficulty;
	difficulty_label.put(" Selected: "+to_string(difficulty));
}
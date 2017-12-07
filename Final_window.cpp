//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//Final_window.cpp

#include "Final_window.h"

//split function from http://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html
vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while(getline(ss, item, delim)){
        tokens.push_back(item);
    }
    return tokens;
}

Final_window::Final_window(Point xy, int w, int h, const bool& won, const string& score, const bool& bonus)
: Window(xy,w,h,split(score, ':')[0]+" - "+(won ? "Victory!" : "Defeat!")),
  score_label(Point(150,y_max()/2-20),"Your Score: "+(won ? split(score, ':')[1] : "0")),
  replay_button(Point(w-80,0),80,40,"Play Again",[](Address, Address pw){reference_to<Final_window>(pw).clicked_replay();}),
  quit_button(Point(w-600,0),80,40,"Quit Game",[](Address, Address pw){reference_to<Final_window>(pw).clicked_next();}),
  blankback(Point(0,0), "back2.jpg"),
  bonus_label(Point(x_max()/2-200,y_max()/2),"+1000 BONUS points for beating the highest 'possible' score!!")
{
	score_label.set_color(won ? Color::black : Color::red);
	score_label.set_font_size(40);
	attach(blankback);
	attach(score_label);
	attach(replay_button);
	attach(quit_button);
	if(bonus) attach(bonus_label);//Display additional message if they got the super bonus
}
//close the window (exits the program as well)
void Final_window::clicked_next(){
	hide();
}
//closes the window and sets the replay flag to 'true'
void Final_window::clicked_replay(){
	replay = true;
	hide();
}
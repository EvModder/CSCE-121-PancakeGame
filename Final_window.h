//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//Final_window.h

#include "lib/Window.h"
#include "lib/GUI.h"
#include "lib/Graph.h"
using namespace Graph_lib;

//class definition for Final_window, used after the Game_window closes to display results
class Final_window : public Graph_lib::Window{
	private:
		Image blankback;
		Button replay_button;
		Button quit_button;
		Text score_label, bonus_label;
		bool replay = false;//whether to replay game
		
	public:
		Final_window(Point, int, int, const bool&, const string&, const bool&);
		void clicked_next();
		void clicked_replay();
		void show_super_bonus();
		bool play_again() const { return replay; }//called by main.cpp to determine whether to play again
};

vector<string> split(const string &s, char delim);
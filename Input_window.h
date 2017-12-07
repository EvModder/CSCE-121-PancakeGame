//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//Input_window.h

#include "lib/Window.h"
#include "lib/GUI.h"
#include "lib/Graph.h"
using namespace Graph_lib;

//Definition of the Input_window class, which prompts the user for their initials and prefered
//difficulty level, as well as showing highscores of previous games
class Input_window : public Graph_lib::Window{
	private:
		Button next_button;
		Button quit_button;
		In_box initials_input;
		Rectangle highscores_box;
		Vector<Text*> scores_text;
		Out_box difficulty_label;
		vector<Button*> difficulty_buttons;
		int difficulty = 9;//default difficulty
		bool chose_quit = true;//whether to exit program when window closes
		
	public:
		Input_window(Point, int, int, const string&, int, vector<string>);
		~Input_window();
		void quit();
		void next();
		void pick_difficulty(Address);
		bool pressed_quit() const { return chose_quit; }//whether the user pressed the quit button
		int get_difficulty() const { return difficulty; }//returns the difficulty inputed by the user
		
		//returns the user's initials, if found.  If no initials were entered, returns ___
		string get_initials() { return initials_input.get_string().empty() ?
									"___" : initials_input.get_string(); }
};
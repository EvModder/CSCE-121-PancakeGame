//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//Game_window.h

#include "lib/Window.h"
#include "lib/GUI.h"
#include "lib/Graph.h"
#include "Pancake.h"
using namespace Graph_lib;

//Game_window class header -- this class is where most of the action takes place
class Game_window : public Graph_lib::Window{
private:
	int moves=0, min_moves;
	Button quit_button;
	Button flip_button;
	Button hint_button;
	Text hint_label;
	Text can_do_in_label;
	In_box flip_select;
	vector<Pancake*> pancakes;
	vector<int> colors;
	Text info_label;
	thread countdown_thread;
	Text time_left, moves_made;
	bool chose_quit = true;//whether to exit program when window closes
	bool won_game = false;//whether the player won the game
	
public:
	Game_window(Point, int, int, const String&, int);
	~Game_window();
	
	//functions used by the Game_window
	void quit();
	void next();
	void victory_stage();
	void set_time_left(int);
	void flip_pancakes();
	void give_hint();
	
	//getters used by main.cpp
	bool pressed_quit() const { return chose_quit; }
	bool won() const { return won_game; }
	int get_moves() const { return moves; }
	int get_min_moves() const { return min_moves; }
};

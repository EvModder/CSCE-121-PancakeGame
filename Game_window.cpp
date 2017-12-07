//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//Game_window.cpp

#include "lib/std_lib_facilities_4.h"
#include "lib/randint.h"
#include "Game_window.h"
#include "find_solution.h"

//extension of find_solution provided by instructor, can handle pancake vectors larger then 9
vector<int>* find_solution(const vector<Pancake*>& pancakes){
	vector<int> v(pancakes.size());
	//copies the values of the pancakes into a vector of ints in reverse order with values 1-difficulty
	for(int i=0; i<pancakes.size(); ++i) v[i] = pancakes[i]->get_num();

	if(v.size() <= 9) return find_solution(v);//no need to do anything fancy. Just return the normal find_solution
	
	vector<int>* solutions = new vector<int>();
	for(int search_i=v.size(); search_i>9; --search_i){
		for(int i=0; i<v.size(); ++i){
			if(v[i] == search_i){
				if(i+1 == search_i);//already in position
				else if(i == 0) solutions->push_back(search_i);
				else{
					solutions->push_back(i+1);
					solutions->push_back(search_i);
				}
				break;
			}
		}
	}
	vector<int> sub_v;
	for(auto k : v) if(k <= 9) sub_v.push_back(k);
	vector<int>* sub_v_solutions = find_solution(sub_v);
	for(auto k : *sub_v_solutions) solutions->push_back(k);
	return solutions;
}

//determines & returns the minimum # of moves required to sort a particular stack of pancakes
int find_min_moves(const vector<Pancake*>& pancakes){
	vector<int>* solution = find_solution(pancakes);
	int min_moves = solution->size();
	delete solution;
	return min_moves;
}
//swap two pancake pointers and the location of the center of the pancakes they point to
void swap(Pancake*& a, Pancake*& b){
	Pancake* c = a;
	a = b; b = c;
	Point a_center = a->get_center();
	a->set_center(b->get_center());
	b->set_center(a_center);
}
//flips a pancake and all the pancakes above it up to the top pancake by reversing their order
void flip_all_above(Vector<Pancake*>& pancakes, int index){
	for(int i=0; i<(index+1)/2; ++i){
		swap(pancakes[index-i],pancakes[i]);
	}
}
//checks if a vector of pancakes is sorted
bool is_sorted(const Vector<Pancake*>& pancakes){
	if(pancakes.size() == 0) return true;
	
	for(int i=1, last_num=pancakes[0]->get_num(); i<pancakes.size(); ++i){
		//if this pancake is shorter then the one above it
		if(pancakes[i]->get_num() < last_num) return false;
		last_num = pancakes[i]->get_num();
	}
	return true;
}
//shuffles a vector of pancakes and returns the shuffled vector
void shuffle(Vector<Pancake*>& pancakes){
	for(int random_i,i=0; i<pancakes.size(); ++i){
		//seeds randint() with randint()+i
		//the reason for this is to prevent nasty infinite loops from randint()'s invertibility
		random_i = randint(randint()+i)%pancakes.size();
		if(i != random_i){
			swap(pancakes[i], pancakes[random_i]);
//			cout << "swapped " << i << " and " << random_i << endl;
		}
	}
//	cout << "Shuffle success: " << !is_sorted(pancakes) << endl;
}

//countdown loop run in a thread for the game timer
void run_countdown(Game_window* win, int time){
	while(--time >= 0){
		if(win->won()) return;
		
		system("sleep 1");
		win->set_time_left(time);
	}
	win->next();
}


//Game_window constructor, initializes buttons, text labels, and pancakes
Game_window::Game_window(Point xy, int w, int h, const String& title, int num_of_pancakes)
:	Window(xy,w,h,title), pancakes(num_of_pancakes),
	quit_button(Point(w-70,0),70,20,"Quit",
		[](Address,Address pw){reference_to<Game_window>(pw).quit();}),
	flip_button(Point(161,0),100,20,"Flip Pancakes",
		[](Address, Address pw){reference_to<Game_window>(pw).flip_pancakes();}),
	hint_button(Point(w/2-50,60),100,80,"Hint!",
		[](Address, Address pw){reference_to<Game_window>(pw).give_hint();}),
	hint_label(Point(w/2-46,160), ""),
	can_do_in_label(Point(270,40),""),
	flip_select(Point(80,0),80,20,"Pancake#:"),
	info_label(Point(10,40),"Top is pancake1, Bottom is pancake"+to_string(num_of_pancakes)),
	countdown_thread(run_countdown,this,num_of_pancakes*10),//time = num of pancakes * 10 seconds
	time_left(Point(270,15), "Time remaining: "+to_string(num_of_pancakes*10)),
	moves_made(Point(410,15), "Flips made: 0"),
	colors{1,2,3,4,5,6,7,8,9,10,11,12}//put nice colors here
{
	for(int i=0; i<num_of_pancakes; ++i){//create the vector of pancakes
		int rand_idx = randint()%colors.size();
		pancakes[i] = new Pancake(Point(w/2,h-((num_of_pancakes-i)*15+5)),i+1, colors[rand_idx]);
		colors.erase(colors.begin()+rand_idx);
	}
	do{shuffle(pancakes);}while(is_sorted(pancakes));//is this acceptable?
	min_moves = find_min_moves(pancakes);//calculate the min # of moves to win
	can_do_in_label.set_label("Can be done in: "+to_string(min_moves)+" moves");
	
	//attach stuff
	for(auto k : pancakes) attach(*k);
	attach(hint_button);
	attach(hint_label);
	attach(can_do_in_label);
	attach(info_label);
	attach(quit_button);
	attach(flip_button);
	attach(flip_select);
	attach(time_left);
	attach(moves_made);
}

Game_window::~Game_window(){
//	countdown_thread.join();
	countdown_thread.detach();//properly dispose of thread (although it is usually already dead by here)
//	countdown_thread.terminate();
	for(auto k : pancakes)
		delete k;
}

//give a hint to the player - put it on the hint_label
void Game_window::give_hint(){
	hint_label.set_label("Index to flip: "+to_string((*find_solution(pancakes))[0]));
	redraw();
}
//called when the flip_button is pressed, determined if input is valid & flips pancakes
void Game_window::flip_pancakes(){
	stringstream ss(flip_select.get_string());
	int pancake_to_flip;
	if(ss >> pancake_to_flip && pancake_to_flip > 1 && pancake_to_flip <= pancakes.size()){
		flip_all_above(pancakes, pancake_to_flip-1);
		moves_made.set_label("Flips made: "+to_string(++moves)),
		can_do_in_label.set_label("Can be done in: "+to_string(find_min_moves(pancakes))+" moves");
		hint_label.set_label("");
		redraw();
		if(is_sorted(pancakes)) victory_stage();//enter the endgame (victory) stage
		
		//not allowed more then min_moves+10, otherwise score would be negative
		else if(moves > min_moves+10) next();
	}
	else{//display error
		//Error_window("Invalid pancake index! Only accepts integer values");//popup error window
		cout << "Invalid pancake index! - Input received: " << flip_select.get_string() << endl;
	}
}
//sets the remaining time on the timout clock for the game
void Game_window::set_time_left(int time){
	time_left.set_label("Time remaining: "+to_string(time));
	Fl::flush();
	redraw();
	Fl::flush();//nasty, nasty. But hey, this is what it took to get it working
	redraw();
}
//quits program
void Game_window::quit(){
	hide();
}
//closes the window and returns to main
void Game_window::next(){
	chose_quit = false;
	hide();
}
//shows congradulations message, waits 3 seconds, then closes the game window
void Game_window::victory_stage(){
	won_game = true;
	Text gg(Point(x_max()/2-130,y_max()/2), "Congrats you won!!");
	gg.set_font_size(28);
	attach(gg);
	Fl::flush();
	redraw();
	system("sleep 3");
	next();
}
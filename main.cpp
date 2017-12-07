//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//main.cpp
 
#include "lib/std_lib_facilities_4.h"
#include "Input_window.h"
#include "Welcome_window.h"
#include "Game_window.h"
#include "Final_window.h"
using namespace Graph_lib;

const int MAX_DIFFICULTY = 12;
const Point center(Fl::x()+Fl::w()/2,Fl::y()+Fl::h()/2);//center of screen, useful for centering windows

//function to load a vector of the scores from a file (e.g., scores.txt)
vector<string> load_scores(){
	vector<string> scores;
	
	ifstream ifs{"scores.txt"};
	if(!ifs) return scores;//return an empty scores list
	
	string score;
	while(ifs>>score && !score.empty()) scores.push_back(score);
	return scores;
}

//add a score to a vector of scores, inserting it in the proper position relative to other scores
//i.e., if a vector contains {2,4,6,8} and a score of 5 is added, the new vector will be {2,4,5,6,8}
void add_score(vector<string>& scores, string score){
	vector<string> new_scores(scores.size()+1);
	bool put_in_vector = false;
	int i=0;
	for(i; i<scores.size(); ++i){
		if(stoi(split(scores[i], ':')[1]) > stoi(split(score, ':')[1])){
			new_scores[i] = scores[i];
		}
		else{
			new_scores[i] = score;
			put_in_vector = true;
			break;
		}
	}
	if(put_in_vector == false) new_scores[i] = score;
	else for(i; i<scores.size(); ++i) new_scores[i+1] = scores[i];
	scores = new_scores;
}

//save a vector of strings to the file "scores.txt"
void save_scores(const vector<string>& scores){
	ofstream ofs{"scores.txt"};
	if(!ofs) error("Unable to load scores.txt!");
	
	for(auto score : scores)
		ofs << score << endl;
}
//calculate the score of a player using function provided by instructor
int calculate_score(int moves_used, int min_moves, int difficulty){
	int wasted_moves = moves_used - min_moves;
	if(wasted_moves < 0){
		return 100 * difficulty + 1000; //+1000 bonus for using fewer then 'min' moves
	}
	return (100 - 10 * wasted_moves) * difficulty; //provided in project rubric
}

//the program's main, where runtime starts
int main() try {
	bool run_game = true;
	while(run_game){
		//splashscreen
		Welcome_window win1(Point(center.x-500,center.y-281), 1000, 562, "Welcome to Fliparoo!");
		gui_main();
		if(win1.pressed_quit()) return 0;
	  
		//input & old highscores
		vector<string> scores = load_scores();
		Input_window win2(Point(center.x-300,center.y-200), 600, 400, "Setup", MAX_DIFFICULTY, scores);
		gui_main();
		if(win2.pressed_quit()) return 0;
		
		//play game
		Game_window win3(Point(center.x-300,center.y-200), 600, 400, "The game is on!", win2.get_difficulty());
		gui_main();
		if(win3.pressed_quit()) return 0;
		//calculate score (only saves scores that are > 0)
		int score = win3.won() ? calculate_score(win3.get_moves(), win3.get_min_moves(), win2.get_difficulty()) : 0;
		string score_string = win2.get_initials()+':'+to_string(score);
		if(score > 0){
			add_score(scores, score_string);
			save_scores(scores);
		}
		//endgame display with replay button
		Final_window win4(Point(center.x-300,center.y-200), 600, 400, win3.won(), score_string, (score>win2.get_difficulty()*100));
		gui_main();
		run_game = win4.play_again();
	}
}
//error handling
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}
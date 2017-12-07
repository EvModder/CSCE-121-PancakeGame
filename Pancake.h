//Nathaniel Leake, Patrick Kitchens, Saipravallika Nettyam
//CSCE 121-517
//Due: December 3, 2015
//Pancake.h

#include "lib/Graph.h"
#include "lib/randint.h"
using namespace Graph_lib;

//Pancake class extending Shape, utilized by the Game_window
class Pancake : public Shape{
public:
	Pancake(Point xy, int i, int cc) : num(i), c(cc) {add(xy);}
	
	//draw this pancake shape (this function is called automatically by the window)
	void draw_lines() const {
		fl_color(Fl_Color(c));//set color
		fl_pie(point(0).x-(num*20+10),point(0).y,num*40+20-1,12,0,360);//draw elipse
		fl_color(color().as_int());//reset color (to black)
		fl_draw(to_string(num).c_str(),point(0).x-5-(num/10)*5,point(0).y+11);
	}
	
	void set_center(Point p){set_point(0, p);}
	Point get_center() const {return point(0);}
	int get_height() const { return 12;}
	int get_num() const { return num;}
	int get_color() const {return c;}
private:
	int num;//every pancake has a number value and a color
	int c;
};
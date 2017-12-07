all: a.out

a.out: Graph.o randint.o GUI.o Window.o Game_window.o Input_window.o Welcome_window.o Final_window.o main.o
	g++ -std=c++14 -g find_solution.o Graph.o randint.o GUI.o Window.o Game_window.o Input_window.o Welcome_window.o Final_window.o main.o -o a.out -lfltk -lfltk_images
Graph.o: lib/Graph.cpp
	g++ -std=c++14 -g -c lib/Graph.cpp -o Graph.o -lfltk -lfltk_images
randint.o: lib/randint.cpp
	g++ -std=c++14 -g -c lib/randint.cpp -o randint.o -lfltk -lfltk_images
GUI.o: lib/GUI.cpp
	g++ -std=c++14 -g -c lib/GUI.cpp -o GUI.o -lfltk -lfltk_images
Window.o: lib/Window.cpp
	g++ -std=c++14 -g -c lib/Window.cpp -o Window.o -lfltk -lfltk_images
Game_window.o: Game_window.cpp
	g++ -std=c++14 -g -c Game_window.cpp -o Game_window.o -lfltk -lfltk_images
Input_window.o: Input_window.cpp
	g++ -std=c++14 -g -c Input_window.cpp -o Input_window.o -lfltk -lfltk_images
Welcome_window.o: Welcome_window.cpp
	g++ -std=c++14 -g -c Welcome_window.cpp -o Welcome_window.o -lfltk -lfltk_images
Final_window.o: Final_window.cpp
	g++ -std=c++14 -g -c Final_window.cpp -o Final_window.o -lfltk -lfltk_images
main.o: main.cpp
	g++ -std=c++14 -g -c main.cpp -o main.o -lfltk -lfltk_images
clean:
	rm *.o a.out

run:
	./a.out

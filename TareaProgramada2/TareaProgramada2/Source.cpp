#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"

int main() {
	using namespace Graph_lib;
	Simple_window win(Point(200,200),600,500,"Simple Window");

	win.wait_for_button();

	return 0;
}
#include "Ventana.h"

int main() {
	using namespace Graph_lib;
	Ventana win(Point(200, 200), 600, 500, "Menu Principal");
	win.wait_for_button();
	return 0;
}
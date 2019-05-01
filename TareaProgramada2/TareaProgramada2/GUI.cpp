#include "GUI.h"
#include "std_lib_facilities.h"

#include <sstream>

using namespace Graph_lib;


void Button::attach(Graph_lib::Window& win)
{
	pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
	own = &win;
}

int In_box::get_int()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	//	return atoi(pi.value());
	const char* p = pi.value();
	if (!isdigit(p[0])) return -999999;
	return atoi(p);
}

string In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	return string(pi.value());
}

void In_box::attach(Graph_lib::Window& win)
{
	pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
	own = &win;
}

void Out_box::put(int i)
{
	Fl_Output& po = reference_to<Fl_Output>(pw);
	std::stringstream ss;
	ss << i;
	po.value(ss.str().c_str());
}

void Out_box::put(const string& s)
{
	reference_to<Fl_Output>(pw).value(s.c_str());
}

void Out_box::attach(Graph_lib::Window& win)
{
	pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
	own = &win;
}
/*
Menu::Menu(Point xy, int w, int h, Kind kk, const string& s)
	:Widget(xy, w, h, s, 0), k(kk), offset(0)
{
}
*/

int Menu::attach(Button& b)
{
	b.width = width;
	b.height = height;

	switch (k) {
	case horizontal:
		b.loc = Point(loc.x + offset, loc.y);
		offset += b.width;
		break;
	case vertical:
		b.loc = Point(loc.x, loc.y + offset);
		offset += b.height;
		break;
	}
	selection.push_back(&b);
	return int(selection.size() - 1);
}

int Menu::attach(Button* p)
{
	//	owned.push_back(p);
	return attach(*p);
}

void Graph_lib::MenuBar::attach(Window & win)
{
	Fl_Menu_Bar *fl;
	fl= new Fl_Menu_Bar(loc.x, loc.y, width, height, label.c_str());
	fl->add("Archivo/Abrir", 0,open_cb);
	fl->add("Archivo/Salir", 0, close_cb);
	pw = fl;
	own = &win;
}

 


 void Graph_lib::MenuBar::open_cb(Fl_Widget *, void *)
 {
	
	 Fl_Native_File_Chooser fnfc;
	 fnfc.title("Seleccione el archivo");
	 fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	 fnfc.filter("Text\t*.txt\n"
		 "C Files\t*.{cxx,h,c}");
	 fnfc.directory("/var/tmp");           // default directory to use
	 // Show native chooser
	 switch (fnfc.show()) {
	 case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;  // ERROR
	 case  1: printf("CANCEL\n");                      break;  // CANCEL
	 default: printf("PICKED: %s\n", fnfc.filename()); break;  // FILE CHOSEN
	 }

 }

 void Graph_lib::MenuBar::close_cb(Fl_Widget *, void *)
 {
	 exit(0);
 }

 
 
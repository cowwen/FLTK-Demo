#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Buffer.H>
#include <include/EditorWindow.h>

Fl_Window *new_view(){
	Fl_Menu_Bar *m = new Fl_Menu_Bar(0, 0, 640, 30);
	m->copy(menuitems);
	EditorWindow *w = new EditorWindow(400,300,"EditorWindows");
	w->editor = new Fl_Text_Editor(0,30,640, 370);
	textbuf = new Fl_Text_Buffer();
	w->editor->buffer(textbuf);
	textbuf->text("hello,cowwen,How are you?");
	w->resizable(*(w->editor));
//	textbuf->add_modify_callback()
	return (Fl_Window *)w;
}

int main(int argc, char **argv)
{
	Fl_Window *window = new_view();
//	Fl_Box *box = new Fl_Box(20, 40, 300, 100, "Hello, Cowwen!");
//	box->box(FL_UP_BOX);
//	box->labelfont(FL_BOLD + FL_ITALIC);
//	box->labelsize(36);
//	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show(argc, argv);
	return Fl::run();
}

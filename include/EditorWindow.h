#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_File_Chooser.H>
#include <errno.h>

int            changed = 0;
char           filename[256] = "";
Fl_Text_Buffer *textbuf;

void save_file(char *newfile) {
  if (textbuf->savefile(newfile))
    fl_alert("Error writing to file '%s':\n%s.", newfile, strerror(errno));
  else
    strcpy(filename, newfile);
  changed = 0;
  textbuf->call_modify_callbacks();
}

void saveas_cb(void) {
  char *newfile;
  newfile = fl_file_chooser("Save File As?", "*", filename);
  if (newfile != NULL) save_file(newfile);
}
void save_cb(void) {
  if (filename[0] == '\0') {
    // No filename - get one!
    saveas_cb();
    return;
}
  else save_file(filename);
}

int check_save(void) {
  if (!changed) return 1;
  int r = fl_choice("The current file has not been saved.\n"
                    "Would you like to save it now?",
                    "Cancel", "Save", "Discard");
  if (r == 1) {
    save_cb(); // Save the file...
    return !changed;
}
  return (r == 2) ? 1 : 0;
}

void new_cb(Fl_Widget*, void* v){
	if (!check_save()) return;
	filename[0] = '\0';
	textbuf->select(0, textbuf->length());
	textbuf->remove_selection();
	changed = 0;
	textbuf->call_modify_callbacks();
}

Fl_Menu_Item menuitems[] = {
	{"&File", 0, 0, 0, FL_SUBMENU},
	{"&New File", 0, (Fl_Callback *)new_cb},
	{0}
};

class EditorWindow : public Fl_Double_Window{
public:
	EditorWindow(int w, int h, const char* t):Fl_Double_Window(w, h, t){}
	~EditorWindow();

	Fl_Window *replace_dlg;
	Fl_Input *replace_find;
	Fl_Input *replace_with;
	Fl_Button *replace_all;
	Fl_Return_Button *replace_next;
	Fl_Button *replace_cancel;

	Fl_Text_Editor *editor;
	char search[256];
};

EditorWindow::~EditorWindow(){
	delete replace_dlg;
	delete replace_dlg;
	delete replace_find;
	delete replace_with;
	delete replace_all;
	delete replace_next;
	delete replace_cancel;
}
/*
void new_cb(Fl_Widget*, void*) {
  if (!check_save()) return;
  filename[0] = ¡¯\0¡¯;
  textbuf->select(0, textbuf->length());
  textbuf->remove_selection();
  changed = 0;
  textbuf->call_modify_callbacks();
}*/
#endif

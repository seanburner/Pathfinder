// *********************************************************************************************************
// Program    : PathFinder 
// File       : Application.cclass
// Author     : Sean A. Burner 
// Inception  : 2025-07
// Details    : gtkmm application gui file directory interactions 
// Compilation:  g++ -o PathFinder main.cpp `pkg-config --cflags --libs gtkmm-4.0`
// Notes      : 
// *********************************************************************************************************

#include <iostream>
#include <gtkmm.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>

#include "src/AppWindow.cclass"

#ifndef PATHFINDER_H
#define PATHFINDER_H
#endif





int main(int argc, char *argv[]) 
{
    auto app = Gtk::Application::create("org.aegesnet.PathFinder");
    int Width = 800, Height = 500;

//    Gtk::Window window;
//    window.set_title("PathFindar App");
//    window.set_default_size(Width, Height);

//    Gtk::Label label("Hello, GTK4!");
//    window.set_child(label);

    return app->make_window_and_run<AppWindow>(argc, argv);		//app->run(window);
}

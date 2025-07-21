#include <gtkmm.h>
#include <gdk/gdkkeysyms.h> // For GDK_KEY_Escape
#include <iostream>       // For std::cerr

class MyWindow : public Gtk::Window
{
public:
    MyWindow()
    {
        // 1. Set the window to be undecorated
        set_decorated(false);

        // 2. Remove the problematic set_surface_type call.
        // In GTK4, for a Gtk::Window, the surface type is generally handled
        // internally. If you need a 'popup' type window that is
        // not a main application window, you'd typically make it transient
        // for another window or create it specifically as a popup.
        // For an undecorated standalone window like this, TOPLEVEL is the
        // default and what we want, and it's implicitly handled.
        // set_surface_type(Gdk::Surface::SurfaceType::TOPLEVEL); // Removed

        // 3. Set a fixed size (often desired for custom shapes)
        set_default_size(400, 300);
        set_resizable(false);

        // 4. (Optional) Set the window to skip taskbar/pager
        // As discussed, direct methods are gone. For an undecorated window
        // that's meant to be a transient popup or notification, consider
        // making it transient for another window (set_transient_for()).
        // For a main undecorated window, it will likely still appear in the taskbar
        // unless the window manager has specific rules for undecorated windows.
        // If you truly need to hide from taskbar, this often requires
        // platform-specific hints or making it a Gtk::Window::POPUP.

        // 5. Apply CSS for rounded corners and transparency
        auto display = get_display();
        if (!display) {
            std::cerr << "Error: Could not get default display." << std::endl;
            // Handle error appropriately, e.g., throw std::runtime_error
            return;
        }

        auto css_provider = Gtk::CssProvider::create();
        css_provider->load_from_data(
            "window {"
           // "  background-color: rgba(0, 0, 0, 0);" // Make the window itself fully transparent
            "}"
            "window.background {"
            "  background-color: rgba(0, 0, 0, 0.5);" // Semi-transparent black for the content area
            "  border-radius: 20px;"                   // Rounded corners
            "}"
        );

        Gtk::StyleContext::add_provider_for_display(display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        // 6. Add content to your window
        auto frame = Gtk::manage(new Gtk::Frame());
        frame->set_margin(20);

        Gtk::Label* label = Gtk::manage(new Gtk::Label("Hello, Curved Window!"));
        frame->set_child(*label);

        set_child(*frame);

        // 7. Connect a signal to close the window (e.g., on Escape key press)
        auto key_controller = Gtk::EventControllerKey::create();
        key_controller->signal_key_pressed().connect(sigc::mem_fun(*this, &MyWindow::on_key_pressed), false);
        add_controller(key_controller);
    }

    // New signature for key event handling in GTK4
    bool on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state)
    {
        if (keyval == GDK_KEY_Escape)
        {
            hide(); // Close the window
            return true; // Event handled
        }
        return false; // Event not handled, continue propagation
    }
};

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.examples.curvedwindow");
    return app->make_window_and_run<MyWindow>(argc, argv);
}

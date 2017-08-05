#include "MainWindow.hpp"


int main(int argc, char** argv)
{

    /* Starts the application */
    gtk_init(&argc, &argv);
    
    GtkBuilder* gtkBuilder = gtk_builder_new();
    MainWindow* window = new MainWindow(*gtkBuilder);
    
    gtk_builder_connect_signals(gtkBuilder, window);
    gtk_main();


    return 0;
}


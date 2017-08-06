#ifndef HANDLERS_HPP
#define HANDLERS_HPP


extern "C" {

    void insert_object(GtkWidget* widget, MainWindow* window)
    {
        /* Draw a line. Only for debug */
        window->insert_line();
    }

    void close_window()
    {
        /* Close the interface window */
        gtk_main_quit();
    }
    
    gboolean configure_event(GtkWidget* widget)
    {
        /* Creates a new surface */
        if(surface)
            cairo_surface_destroy(surface);

        surface = gdk_window_create_similar_surface (
                                        gtk_widget_get_window(widget),
                                        CAIRO_CONTENT_COLOR,
                                        gtk_widget_get_allocated_width(widget),
                                        gtk_widget_get_allocated_height(widget)
                                        );

        /* Creates a cairo context over the surface */
        cairo_t *cr = cairo_create(surface);
        cairo_paint(cr);
        cairo_destroy(cr);

        /* Returning TRUE to avoide another call of the function */
        return TRUE;
    }

    gboolean draw(GtkWidget* widget, cairo_t* cr, MainWindow* main_window)
    {
        /* Redraw a cairo context */
        main_window->redraw(cr);
        return FALSE;
    }


}

#endif // HANDLERS_HPP

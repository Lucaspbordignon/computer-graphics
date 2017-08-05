#ifndef HANDLERS_HPP
#define HANDLERS_HPP


extern "C" {

    void insert_object(MainWindow* window)
    {
        /* Draw a point. Only for debug */
        window->insert_point();
    }

    void close_window()
    {
        /* Close the interface window */
        gtk_main_quit();
    }

    void configure_event(GtkWidget* widget)
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
        cairo_t* cr = cairo_create(surface);
        cairo_set_source_rgb (cr, 1, 1, 1);
        cairo_paint (cr);
        cairo_destroy (cr);
    }

    void draw(GtkWidget* widget, cairo_t* cr)
    {
        /* Redraw a cairo context */
        cairo_set_source_surface(cr, surface, 0, 0);
        cairo_paint(cr);
    }

}

#endif // HANDLERS_HPP

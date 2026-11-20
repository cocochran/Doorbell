#include "client.h"
#include "payload.h"

#if defined(__has_include)
#  if __has_include(<gtk/gtk.h>)
#    include <gtk/gtk.h>
#  elif __has_include(<gtk-4.0/gtk/gtk.h>)
#    include <gtk-4.0/gtk/gtk.h>
#  elif __has_include(<gtk-3.0/gtk/gtk.h>)
#    include <gtk-3.0/gtk/gtk.h>
#  else
#    include <gtk/gtk.h>
#  endif
#else
#  include <gtk/gtk.h>
#endif



static void button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        send_payload();
    }
}
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    g_signal_connect(window, "button_press_event", G_CALLBACK(button_press_event), NULL);
    gtk_widget_set_size_request(window, 200, 100);
    gtk_window_set_title(GTK_WINDOW(window), "Doorbell");
    gtk_window_present(GTK_WINDOW(window));
}



int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.doorbell", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
#include "client.h"
#include "payload.h"
#include <gtk/gtk.h>




static void button_press_event(
    GtkWidget *widget, 
    GdkEvent *event, 
    gpointer user_data,
    MQTTClient* client,
    MQTTClient_message* msg,
    MQTTClient_deliveryToken* token,
    Payload* payload
    ) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        pass_payload_to_broker();
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

    MQTTClient client;
    MQTTClient_message msg;
    MQTTClient_deliveryToken token;
    MQTTClient_connectOptions connection_options;
    Payload payload;

    initialize_session(&client, &msg, &connection_options);
    
    return status;
}
#include "client.h"
#include "payload.h"
#include <gtk/gtk.h>
#include <stdio.h>


typedef struct {
    MQTTClient client;
    MQTTClient_message msg;
    MQTTClient_deliveryToken token;
    MQTTClient_connectOptions connection_options;
    Payload payload;
} AppState;


static void on_pressed(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data) {
    (void)gesture; 
    (void)n_press; 
    (void)x; 
    (void)y;
    AppState *state = user_data;
    pass_payload_to_broker(state->client, state->msg, state->token, &state->payload);
    printf("hi\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    GtkGesture *click = gtk_gesture_click_new();
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(click), 0); /* any mouse button */
    g_signal_connect(click, "pressed", G_CALLBACK(on_pressed), user_data);
    gtk_widget_add_controller(window, GTK_EVENT_CONTROLLER(click));
    gtk_widget_set_size_request(window, 200, 100);
    gtk_window_set_title(GTK_WINDOW(window), "Doorbell");
    gtk_window_present(GTK_WINDOW(window));
}


int main(int argc, char **argv) {
    AppState state = {0};
    initialize_session(&state.client, &state.msg, &state.connection_options);

    GtkApplication *app = gtk_application_new("com.example.doorbell", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), &state);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

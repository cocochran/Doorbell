#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"

void load_env(const char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL) return;

    char line[256];
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        if (line[0] == "#" || line[0] == '\0') continue;

        char *eq = strchr(line, '=');
        if (eq) {
            *eq = '\0';
            setenv(line, eq + 1, 1);
        }
    }
    fclose(file);
}

int main (int argc, char* argv[]){
    load_env(".env");
    MQTTClient client;
    const char* url = getenv("URL");
    int rc = MQTTClient_create(&client, url, MQTT_PERSISTENCE_NONE, NULL);

    if (rc != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to connect to MQTT broker.  Return code: %d\n", rc);
        _exit(EXIT_FAILURE);
    }
}

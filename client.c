#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "payload.h"

void load_env(const char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL) return;

    char line[256];
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        if (line[0] == '#' || line[0] == '\0') continue;

        char *eq = strchr(line, '=');
        if (eq) {
            *eq = '\0';
            setenv(line, eq + 1, 1);
        }
    }
    fclose(file);
}

int pass_payload_to_broker(MQTTClient client, MQTTClient_message msg, MQTTClient_deliveryToken token, Payload* payload){
    msg.payload = payload;
    msg.retained = 0;
    int rc;

    rc = MQTTClient_publishMessage(client, RESPONSE, &msg, &token);

    if (rc != MQTTCLIENT_SUCCESS){
        fprintf(stderr, "Failed to publish message.  Return code: %d\n", rc);
        exit(EXIT_FAILURE);
    } 
    return rc;
}

int initialize_session(MQTTClient client, MQTTClient_message msg, MQTTClient_connectOptions connection_options){
    load_env(".env");
    const char* url = getenv("URL");
    int rc; 
    
    rc = MQTTClient_create(&client, url, "doorbell", MQTTCLIENT_PERSISTENCE_NONE, NULL);

    if (rc != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to create client.  Return code: %d\n", rc);
        exit(EXIT_FAILURE);
    }

    connection_options.keepAliveInterval = 20;
    connection_options.cleansession = 1;

    rc = MQTTClient_connect(client, &connection_options);

    if (rc != MQTTCLIENT_SUCCESS){
        fprintf(stderr, "Failed to connect to broker.  Return code: %d\n", rc);
        exit(EXIT_FAILURE);
    }
}





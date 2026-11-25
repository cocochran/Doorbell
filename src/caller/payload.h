#ifndef PAYLOAD_H
#define PAYLOAD_H
#include <stdint.h>

#define CALL "CALL"
#define RESPONSE "RESPONSE"
#define TIMEOUT 10000

typedef enum Payload {
    NO = 0,
    YES = 1
} Payload;



#endif
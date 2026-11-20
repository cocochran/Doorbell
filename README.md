# Doorbell Caller & Responder Clients

A smart doorbell that sends a ring to Discord and carries the reply back to the door. Messages travel through an MQTT broker.

## Clients

- **Caller** (`src/Caller/`): runs on the Raspberry Pi at the door. When the bell is pressed, it publishes a call to the MQTT broker. It then waits for a response and shows it at the doorbell.
- **Responder**: receives calls from the MQTT broker and passes them to a Discord bot, which notifies me. My reply in Discord is published back through the broker to the Caller.

## Flow

```
Bell pressed → Caller (Device) → MQTT broker → Responder → Discord bot → User
User → Discord bot → Responder → MQTT broker → Caller (Device) → Doorbell
```

## Dependencies

- [Eclipse Paho MQTT C client](https://github.com/eclipse-paho/paho.mqtt.c)
- GTK 4 (Caller display)

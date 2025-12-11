#ifndef BOX_STATUS_H
#define BOX_STATUS_H

#include <Arduino.h>

class Box_Status {
public:
    enum State {
        NOT_CONNECTED,
        LOCKED,
        UNLOCKED
    };

    Box_Status(uint8_t redPin, uint8_t greenPin, uint8_t connPin);

    void begin();
    void setState(State newState);
    State getStatus() const;    // Ny funktion
    void update();
    void setLocked(bool locked);
    void setDisplayEnabled(bool enabled);

private:
    uint8_t _redPin;
    uint8_t _greenPin;
    uint8_t _connPin;

    State _currentState;
    State _lastKnownState;      // Husk sidste locked/unlocked tilstand
    unsigned long _lastBlinkTime;
    bool _redLedState;
    bool _displayEnabled;

    bool isConnected();
    void applyState();
};

#endif

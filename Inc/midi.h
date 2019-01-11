
#include <stdint.h>

#define STATUS_BITS       4
#define NOTE_OFF          0b1000
#define NOTE_ON           0b1001
#define POLY_KEY_PRESSURE 0b1010
#define CONTROLLER_CHANGE 0b1011
#define PROGRAM_CHANGE    0b1100
#define CHANNEL_PRESSURE  0b1101
#define PITCH_BEND        0b1110

typedef struct MIDIPacket {
    uint8_t status_byte;
    uint8_t data_byte1;
    uint8_t data_byte2;
} MIDIPacket_t;

void processMidi(MIDIPacket_t *p);


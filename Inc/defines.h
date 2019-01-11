// GLOBAL VARIABLES

// VALUES
#define TXBUFFERSIZE                      1
#define RXBUFFERSIZE                      3
#define CMDLINESIZE                      512

// EVENTS
#define COMMAND_RECEIVED                  0
#define MIDI_RECEIVED                     1

// MACROS
#define PRINT(x,y)                        HAL_UART_Transmit(&huart1, x, y, 100)
#define GET_EVENT(EVENT)                  (mainLoopEvents & (0x1 << EVENT)) > 0
#define SET_EVENT(EVENT)                  mainLoopEvents |=  (0x1 << EVENT)
#define UNSET_EVENT(EVENT)                mainLoopEvents &= ~(0x1 << EVENT)

#define commandReceivedEvent()            SET_EVENT(COMMAND_RECEIVED)
#define midiReceivedEvent()               SET_EVENT(MIDI_RECEIVED)

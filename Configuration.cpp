// General Settings

// Defines the serial port baud rate.  Make sure it matches the Bluetooth module's baud rate.
// Recommended value: 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 
#define UART_BAUD_RATE 9600

#define SCALE_X_ENABLED 1
#if SCALE_X_ENABLED > 0
  
  #define SCALE_X_PROTOCOL 3
  #define X_VALUE_FACTOR 1.240207535 / 254.0
  #define X_TRANSMIT_INTERVAL 250
  
  #define X_CLOCK_PIN_BIT 3
  #define X_CLOCK_DDR DDRD
  #define X_CLOCK_INPUT_PORT PIND
 
  #define X_DATA_PIN_BIT 2
  #define X_DATA_DDR DDRD
  #define X_DATA_INPUT_PORT PIND

#endif

#define SCALE_Y_ENABLED 1
#if SCALE_Y_ENABLED > 0
  
  #define SCALE_Y_PROTOCOL 2
  #define Y_VALUE_FACTOR 1.0 / 25.40
  #define Y_TRANSMIT_INTERVAL 250
  
  #define Y_CLOCK_PIN_BIT 5
  #define Y_CLOCK_DDR DDRD
  #define Y_CLOCK_INPUT_PORT PIND
 
  #define Y_DATA_PIN_BIT 4
  #define Y_DATA_DDR DDRD
  #define Y_DATA_INPUT_PORT PIND

#endif

#define SCALE_Z_ENABLED 0
#if SCALE_Z_ENABLED > 0
  
  #define SCALE_Z_PROTOCOL 3
  #define Z_VALUE_FACTOR 1.0
  #define Z_TRANSMIT_INTERVAL 250
  
  #define Z_CLOCK_PIN_BIT 4
  #define Z_CLOCK_DDR DDRB
  #define Z_CLOCK_INPUT_PORT PINB
 
  #define Z_DATA_PIN_BIT 6
  #define Z_DATA_DDR DDRE
  #define Z_DATA_INPUT_PORT PINE

#endif
// General Settings

// Defines the serial port baud rate.  Make sure it matches the Bluetooth module's baud rate.
// Recommended value: 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 
#define UART_BAUD_RATE 9600

// Defines if the X axis is used. 
#define SCALE_X_ENABLED 1

#if SCALE_X_ENABLED > 0

  // Defines the protocol used by the caliper.
  // 0 - Is a debug mode to analyse the caliper's data.
  // 1 - The caliper sends 6 nibbles. 
  // 2 - The caliper sends 7 nibbles. Known as BCD - Binary coded digits.
  // 3 - The caliper sends two blocks with 28 bits.
  //
  // The protocol 1 and 2 are read in a blocking mannor, because
  // of the thight timing in the transmition.
  //
  // The protocol 3 is available in a blocking and a none blocking version.
  // It is recommended not to mix blocking and none blocking protocols.
  //
  // This part of the software isn't yet well tested.
  //
  #define SCALE_X_PROTOCOL 3
  
  // Defines a factor the value to submit is multiplied with.
  #define X_VALUE_FACTOR 1.240207535 / 254.0
  
  // Defines the interval in milliseconds the value is submitted.
  #define X_TRANSMIT_INTERVAL 250
  
  
  // Defines the pin bit for the clock signal.
  #define X_CLOCK_PIN_BIT 3
  
  // Defines the DDR Port for the clock signal.
  #define X_CLOCK_DDR DDRD
  
  // Defines the input port of the clock signal.
  #define X_CLOCK_INPUT_PORT PIND
 
 
  // Defines the pin bit for the data signal.
  #define X_DATA_PIN_BIT 2
  
  // Defines the DDR port for the data signal.
  #define X_DATA_DDR DDRD
  
  // Defines the input port for the data signal.
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
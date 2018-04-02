/*

  ArduinoDROCC (CC stands for "Cheap Chinese" ;-) )

  This work is loosely based on the great work of 
  * Yuriy Krushelnytskiy, http://www.yuriystoys.com
  * Ryszard Malinowski, http://www.rysium.com 
  Without their efford in TouchGRO und the Arduino sketch
  this wouldn't exist.
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Version  0.1 - Initial Release
  
*/

#include "Configuration.cpp"


#if SCALE_X_ENABLED > 0 || SCALE_Y_ENABLED > 0 || SCALE_Z_ENABLED > 0
#define DRO_ENABLED 1
#else
#define DRO_ENABLED 0
#endif

#if SCALE_X_ENABLED > 0
volatile long xValue;
volatile long xReportValue;
volatile bool xClockState;
volatile bool xLastClockState;
volatile long xClockDownCycles;
volatile long xClockUpCycles;
volatile bool xDataState;
volatile byte xBitPos;
unsigned long xLastTransmit;
#endif

#if SCALE_Y_ENABLED > 0
volatile long yValue;
volatile long yReportValue;
volatile bool yClockState;
volatile bool yLastClockState;
volatile long yClockDownCycles;
volatile long yClockUpCycles;
volatile bool yDataState;
volatile byte yBitPos;
unsigned long yLastTransmit;
#endif

#if SCALE_Z_ENABLED > 0
volatile long zValue;
volatile long zReportValue;
volatile bool zClockState;
volatile bool zLastClockState;
volatile long zClockDownCycles;
volatile long zClockUpCycles;
volatile bool zDataState;
volatile byte zBitPos;
unsigned long zLastTransmit;
#endif

void setup() {

// Initialize DRO values
#if DRO_ENABLED > 0

#if SCALE_X_ENABLED > 0
    X_DATA_DDR &= ~_BV(X_DATA_PIN_BIT);
    X_CLOCK_DDR &= ~_BV(X_CLOCK_PIN_BIT);
    xValue = 0L;
    xReportValue = NULL;
    xClockState = 0;
    xLastClockState = 0;
    xClockDownCycles = 0;
    xClockUpCycles = 0;
    xDataState = 0;
    xBitPos = 0;
    xLastTransmit = millis();
#endif

#if SCALE_Y_ENABLED > 0
    Y_DATA_DDR &= ~_BV(Y_DATA_PIN_BIT);
    Y_CLOCK_DDR &= ~_BV(Y_CLOCK_PIN_BIT);
    yValue = 0L;
    yReportValue = NULL;
    yClockState = 0;
    yLastClockState = 0;
    yClockDownCycles = 0;
    yClockUpCycles = 0;
    yDataState = 0;
    yBitPos = 0;
    yLastTransmit = millis();
#endif

#if SCALE_Z_ENABLED > 0
    Z_DATA_DDR &= ~_BV(Z_DATA_PIN_BIT);
    Z_CLOCK_DDR &= ~_BV(Z_CLOCK_PIN_BIT);
    zValue = 0L;
    zReportValue = NULL;
    zClockState = 0;
    zLastClockState = 0;
    zClockDownCycles = 0;
    zClockUpCycles = 0;
    zDataState = 0;
    zBitPos = 0;
    zLastTransmit = millis();
#endif

#endif

    //initialize serial port
	Serial.begin(UART_BAUD_RATE);
}

void loop() {
    
#if DRO_ENABLED > 0

#if SCALE_X_ENABLED > 0

    xClockState = X_CLOCK_INPUT_PORT & _BV(X_CLOCK_PIN_BIT);
    xDataState = X_DATA_INPUT_PORT & _BV(X_DATA_PIN_BIT);

    #if SCALE_X_PROTOCOL == 0

    readScale_analyse(
        xValue,xReportValue,xClockState,
        xLastClockState,xClockDownCycles,xClockUpCycles,
        xDataState,xBitPos,
        X_CLOCK_INPUT_PORT,X_CLOCK_PIN_BIT,
        X_DATA_INPUT_PORT,X_DATA_PIN_BIT
    );
    
    #elif SCALE_X_PROTOCOL == 1
    
    readScale_6x4_nb(
        xValue,xReportValue,xClockState,
        xLastClockState,xClockDownCycles,xClockUpCycles,
        xDataState,xBitPos,
        X_CLOCK_INPUT_PORT,X_CLOCK_PIN_BIT,
        X_DATA_INPUT_PORT,X_DATA_PIN_BIT
    );
    
    #elif SCALE_X_PROTOCOL == 2
    
    readScale_7x4_b(
        xValue,xReportValue,xClockState,
        xLastClockState,xClockDownCycles,xClockUpCycles,
        xDataState,xBitPos,
        X_CLOCK_INPUT_PORT,X_CLOCK_PIN_BIT,
        X_DATA_INPUT_PORT,X_DATA_PIN_BIT
    );
    
    #elif SCALE_X_PROTOCOL == 3
    
    readScale_2x24_b(
        xValue,xReportValue,xClockState,
        xLastClockState,xClockDownCycles,xClockUpCycles,
        xDataState,xBitPos,
        X_CLOCK_INPUT_PORT,X_CLOCK_PIN_BIT,
        X_DATA_INPUT_PORT,X_DATA_PIN_BIT
    );
    
    #endif
    
    if( xReportValue != NULL && millis()-xLastTransmit > X_TRANSMIT_INTERVAL )
    {
        Serial.print(F("X"));
        Serial.print((long)xReportValue*X_VALUE_FACTOR);
        Serial.print(F(";\n"));
        xReportValue = NULL;
        xLastTransmit = millis();
    }
    
    xLastClockState = xClockState; 
    
#endif

#if SCALE_Y_ENABLED > 0

    yClockState = Y_CLOCK_INPUT_PORT & _BV(Y_CLOCK_PIN_BIT);
    yDataState = Y_DATA_INPUT_PORT & _BV(Y_DATA_PIN_BIT);

    #if SCALE_Y_PROTOCOL == 0

    readScale_analyse(
        yValue,yReportValue,yClockState,
        yLastClockState,yClockDownCycles,yClockUpCycles,
        yDataState,yBitPos,
        Y_CLOCK_INPUT_PORT,Y_CLOCK_PIN_BIT,
        Y_DATA_INPUT_PORT,Y_DATA_PIN_BIT
    );
    
    #elif SCALE_Y_PROTOCOL == 1
    
    readScale_6x4_nb(
        yValue,yReportValue,yClockState,
        yLastClockState,yClockDownCycles,yClockUpCycles,
        yDataState,yBitPos,
        Y_CLOCK_INPUT_PORT,Y_CLOCK_PIN_BIT,
        Y_DATA_INPUT_PORT,Y_DATA_PIN_BIT
    );
    
    #elif SCALE_Y_PROTOCOL == 2
    
    readScale_7x4_b(
        yValue,yReportValue,yClockState,
        yLastClockState,yClockDownCycles,yClockUpCycles,
        yDataState,yBitPos,
        Y_CLOCK_INPUT_PORT,Y_CLOCK_PIN_BIT,
        Y_DATA_INPUT_PORT,Y_DATA_PIN_BIT
    );
    
    #elif SCALE_Y_PROTOCOL == 3
    
    readScale_2x24_b(
        yValue,yReportValue,yClockState,
        yLastClockState,yClockDownCycles,yClockUpCycles,
        yDataState,yBitPos,
        Y_CLOCK_INPUT_PORT,Y_CLOCK_PIN_BIT,
        Y_DATA_INPUT_PORT,Y_DATA_PIN_BIT
    );
    
    #endif
    
    if( yReportValue != NULL  && millis()-yLastTransmit > Y_TRANSMIT_INTERVAL)
    {
        Serial.print(F("Y"));
        Serial.print((long)yReportValue*Y_VALUE_FACTOR);
        Serial.print(F(";\n"));
        yReportValue = NULL;
        yLastTransmit = millis();
    }
    
    yLastClockState = yClockState; 
    
#endif

#if SCALE_Z_ENABLED > 0

    zClockState = Z_CLOCK_INPUT_PORT & _BV(Z_CLOCK_PIN_BIT);
    zDataState = Z_DATA_INPUT_PORT & _BV(Z_DATA_PIN_BIT);

    #if SCALE_Z_PROTOCOL == 0

    readScale_analyse(
        zValue,zReportValue,zClockState,
        zLastClockState,zClockDownCycles,zClockUpCycles,
        zDataState,zBitPos,
        Z_CLOCK_INPUT_PORT,Z_CLOCK_PIN_BIT,
        Z_DATA_INPUT_PORT,Z_DATA_PIN_BIT
    );
    
    #elif SCALE_Z_PROTOCOL == 1
    
    readScale_6x4_nb(
        zValue,zReportValue,zClockState,
        zLastClockState,zClockDownCycles,zClockUpCycles,
        zDataState,zBitPos,
        Z_CLOCK_INPUT_PORT,Z_CLOCK_PIN_BIT,
        Z_DATA_INPUT_PORT,Z_DATA_PIN_BIT
    );
    
    #elif SCALE_Z_PROTOCOL == 2
    
    readScale_7x4_b(
        zValue,zReportValue,zClockState,
        zLastClockState,zClockDownCycles,zClockUpCycles,
        zDataState,zBitPos,
        Z_CLOCK_INPUT_PORT,Z_CLOCK_PIN_BIT,
        Z_DATA_INPUT_PORT,Z_DATA_PIN_BIT
    );
    
    #elif SCALE_Z_PROTOCOL == 3
    
    readScale_2x24_b(
        zValue,zReportValue,zClockState,
        zLastClockState,zClockDownCycles,zClockUpCycles,
        zDataState,zBitPos,
        Z_CLOCK_INPUT_PORT,Z_CLOCK_PIN_BIT,
        Z_DATA_INPUT_PORT,Z_DATA_PIN_BIT
    );
    
    #endif
    
    if( zReportValue != NULL  && millis()-zLastTransmit > Z_TRANSMIT_INTERVAL )
    {
        Serial.print(F("Z"));
        Serial.print((long)zReportValue*Z_VALUE_FACTOR);
        Serial.print(F(";\n"));
        zReportValue = NULL;
        zLastTransmit = millis();
    }
    
    zLastClockState = zClockState; 
    
#endif

#endif

}

#if SCALE_X_PROTOCOL == 3 || SCALE_Y_PROTOCOL == 3 || SCALE_Z_PROTOCOL == 3

inline void readScale_2x24_b( 
    volatile long &Value,
    volatile long &ReportValue,
    volatile bool &ClockState,
    volatile bool &LastClockState,
    volatile long &ClockDownTime,
    volatile long &ClockUpTime,
    volatile bool &DataState,
    volatile byte &BitPos,
    volatile byte &CLOCK_INPUT_PORT,
    volatile byte CLOCK_PIN_BIT,
    volatile byte &DATA_INPUT_PORT,
    volatile byte DATA_PIN_BIT
){
    
    //
    // this protocol comes in such a 
    // hurry we have to read it in a blocking state.
    //
    
    // we wait for a long up time 
    ClockUpTime = 0;
    while( ClockUpTime < 30000)
    {
        if(CLOCK_INPUT_PORT & _BV(CLOCK_PIN_BIT))
            ClockUpTime++;
        else
            ClockUpTime = 0;
    }
    BitPos = 0;
    Value = 0L;
    
    // now we read the data
    while(true)
    {
        
        // wait for falling clock line.
        while( CLOCK_INPUT_PORT & _BV(CLOCK_PIN_BIT) ){}
        
        // wait for raising clock line
        while( !(CLOCK_INPUT_PORT & _BV(CLOCK_PIN_BIT)) ) {}
    
        DataState = DATA_INPUT_PORT & _BV(DATA_PIN_BIT);
        
        if(BitPos > 24 && BitPos <= 47)
        {
            
            // read data bit
            if(DataState)
            {
                Value |= ((long)0x800000 );
                //Value |= 1;
            }
            
            if( BitPos < 47)
                Value >>= 1;

        }
        
        if( BitPos == 47)
        {
            
            if (DataState)
            {
                Value |= 0xFF000000;
            }
            
            ReportValue = Value;
            return;
        }

        BitPos++;            

    }
    
}

#endif

#if SCALE_X_PROTOCOL == 2 || SCALE_Y_PROTOCOL == 2 || SCALE_Z_PROTOCOL == 2

inline void readScale_7x4_b( 
    volatile long &Value,
    volatile long &ReportValue,
    volatile bool &ClockState,
    volatile bool &LastClockState,
    volatile long &ClockDownTime,
    volatile long &ClockUpTime,
    volatile bool &DataState,
    volatile byte &BitPos,
    volatile byte &CLOCK_INPUT_PORT,
    volatile byte CLOCK_PIN_BIT,
    volatile byte &DATA_INPUT_PORT,
    volatile byte DATA_PIN_BIT
){
    
    byte dig[6];
    dig[0] = 0;
    dig[1] = 0;
    dig[2] = 0;
    dig[3] = 0;
    dig[4] = 0;
    dig[5] = 0;
    
    //
    // this protocol comes in such a 
    // hurry we have to read it in a blocking state.
    //
    
    // we wait for a long up time 
    ClockUpTime = 0;
    while( ClockUpTime < 30000)
    {
        if(CLOCK_INPUT_PORT & _BV(CLOCK_PIN_BIT))
            ClockUpTime++;
        else
            ClockUpTime = 0;
    }
    BitPos = 0;
    
    // now we read the data
    while(BitPos < 28)
    {
        
        // wait for falling clock line.
        while( CLOCK_INPUT_PORT & _BV(CLOCK_PIN_BIT) ){}
        
        // wait for raising clock line
        while( !(CLOCK_INPUT_PORT & _BV(CLOCK_PIN_BIT)) ) {}
    
        DataState = DATA_INPUT_PORT & _BV(DATA_PIN_BIT);
        
        if(BitPos < 4)
        {
            
            // read data bit
            if(!DataState)
                dig[0] |= ((long)0x8 );
            if(BitPos < 3)
                dig[0] >>= 1;

        }
        else if(BitPos < 8)
        {
            
            // read data bit
            if(!DataState)
                dig[1] |= ((long)0x8 );
            if(BitPos < 7)
                dig[1] >>= 1;

        }
        else if(BitPos < 12)
        {
            
            // read data bit
            if(!DataState)
                dig[2] |= ((long)0x8 );
            if(BitPos < 11)
                dig[2] >>= 1;
            
        }
        else if(BitPos < 16)
        {
            
            // read data bit
            if(!DataState)
                dig[3] |= ((long)0x8 );
            if(BitPos < 15)
                dig[3] >>= 1;
        }
        else if(BitPos < 20)
        {
            
            // read data bit
            if(!DataState)
                dig[4] |= ((long)0x8 );
            if(BitPos < 19)
                dig[4] >>= 1;
        }
        else if(BitPos < 24)
        {
            
            // read data bit
            if(!DataState)
                dig[5] |= ((long)0x8 );
            if(BitPos < 23)
                dig[5] >>= 1;
        }
        else if( BitPos == 24)
        {

            ReportValue = 0L;
            
            ReportValue += (dig[5]*100000);
            ReportValue += (dig[4]*10000);
            ReportValue += (dig[3]*1000);
            ReportValue += (dig[2]*100);
            ReportValue += (dig[1]*10);
            ReportValue += (dig[0]*1);
        
            if(!DataState)
                ReportValue = -ReportValue;
            return;
            
        }

        BitPos++;            

    }
    
}

inline void readScale_7x4_nb( 
    volatile long &Value,
    volatile long &ReportValue,
    volatile bool &ClockState,
    volatile bool &LastClockState,
    volatile long &ClockDownTime,
    volatile long &ClockUpTime,
    volatile bool &DataState,
    volatile byte &BitPos,
    volatile byte &CLOCK_INPUT_PORT,
    volatile byte CLOCK_PIN_BIT,
    volatile byte &DATA_INPUT_PORT,
    volatile byte DATA_PIN_BIT
){
    
    if( !LastClockState && ClockState)
    { 

        if(ClockUpTime > 100000)
            BitPos = 0;
        
        ClockUpTime = 1;
        
        if( BitPos < 28)
        {
            
            if (!DataState)
                Serial.print(F("0"));
            else
                Serial.print(F("1"));
            
        }
        else if( BitPos == 28)
        {
            Serial.print(F("\n"));
        }
        
        BitPos++;
        return;
        
    }
    else if( LastClockState && ClockState)
    {
        ClockUpTime++;
        return;
    }
    /*
    else if( !LastClockState && !ClockState)
    {
        ClockDownTime++;
        return;
    }
    /**/
    
}
#endif

#if SCALE_X_PROTOCOL == 1 || SCALE_Y_PROTOCOL == 1 || SCALE_Z_PROTOCOL == 1
inline void readScale_6x4_nb( 
    volatile long &Value,
    volatile long &ReportValue,
    volatile bool &ClockState,
    volatile bool &LastClockState,
    volatile long &ClockDownTime,
    volatile long &ClockUpTime,
    volatile bool &DataState,
    volatile byte &BitPos,
    volatile byte &CLOCK_INPUT_PORT,
    volatile byte CLOCK_PIN_BIT,
    volatile byte &DATA_INPUT_PORT,
    volatile byte DATA_PIN_BIT
){
    
    if( LastClockState && !ClockState)
    { 

        // We wait for a longer pause
        // in the clock signal
        // to recognize the first bit
        if( ClockDownTime > 10000)
        {
            Value = 0;
            BitPos = 0;
            ClockDownTime = 0;
        }
        
        // reading data bits
        if( BitPos < 20)
        {
            
            if (!DataState)
                Value |= ((long)0x00100000 );
            
			Value >>= 1;
            
        // reading sign
        }
        else if( BitPos == 20)
        {

            if (!DataState)
            {
                Value = ~Value;
            }
        
        // sending data
        }
        else if( BitPos == 23)
        {
            ReportValue = Value;
        }
        
        BitPos++;
        
    }else if( !LastClockState && !ClockState)
        ClockDownTime++;
    
}
#endif

#if SCALE_X_PROTOCOL == 0 || SCALE_Y_PROTOCOL == 0 || SCALE_Z_PROTOCOL == 0
inline void readScale_analyse( 
    volatile long &Value,
    volatile long &ReportValue,
    volatile bool &ClockState,
    volatile bool &LastClockState,
    volatile long &ClockDownTime,
    volatile long &ClockUpTime,
    volatile bool &DataState,
    volatile byte &BitPos,
    volatile byte &CLOCK_INPUT_PORT,
    volatile byte CLOCK_PIN_BIT,
    volatile byte &DATA_INPUT_PORT,
    volatile byte DATA_PIN_BIT
){
    
    if( LastClockState && ClockState)
    {
        ClockUpTime++;
        return;
    }
    else if( !LastClockState && !ClockState)
    {
       ClockDownTime++;
       return;
    }
    else if( LastClockState && !ClockState)
    { 

        Serial.print("U:");
        Serial.print(ClockUpTime);
        //Serial.print("       data:");
        //Serial.print(DataState);
        Serial.print("\n");
        ClockUpTime = 1;
        return;
    }
    else //if( !LastClockState && ClockState)
    { 
        
        Serial.print("D:");
        Serial.print(ClockDownTime);
        //Serial.print("       data:");
        //Serial.print(DataState);
        Serial.print("\n");
        ClockUpTime = 1;
        return;
        
    }

}
#endif

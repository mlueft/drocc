
void loop(){
	xClockState = readClock


	if( !xLastClockState && xClockState)
	{	
		if(xBitPos == 21){
			// set sign
			
			xReportValue = xValue;
			xValue = 0;
			xBitPos = 0;
			
		}elif(xBitPos < 20){
			// set pit
			
			xBitPos++;
			
		}
	}
	xLastClockState = xClockState;


	if(xReportValue != Null){

		//send xReportValue to serial
		
		xReportValue = Null;
	}

}












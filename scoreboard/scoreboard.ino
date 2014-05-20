//Lines to the shiftregisters
const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;
const int reset = 2;
const int outputenable = 3;
const int segments = 9;

/*#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "boardControl.h"
#include "boardVars.h"
#include "buttonVars.h"
*/

//What segments are upside down?
const int dir[] = {0,0,0,1,0,1,0,0,0};

//What LEDs do we light for each number?
const byte leds[10][7] = {{1,1,1,1,1,1,0},{0,1,1,0,0,0,0},{1,1,0,1,1,0,1},{1,1,1,1,0,0,1},{0,1,1,0,0,1,1},{1,0,1,1,0,1,1},{1,0,1,1,1,1,1},{1,1,1,0,0,0,0},{1,1,1,1,1,1,1},{1,1,1,0,0,1,1}};

//What are the values associated with the LEDs?
const byte pins[2][8] = {{16,32,128,64,1,4,2,8},{4,2,32,64,128,8,16,1}};

//How do we remap the pins if the LED is upside down?
const byte remap[2][8] = {{0,1,2,3,4,5,6,7},{3,4,5,0,1,2,6,7}};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(reset, OUTPUT);  
  pinMode(outputenable, OUTPUT);
  digitalWrite(reset,HIGH);
  digitalWrite(outputenable,HIGH);
//  initialTime = tv.tv_sec;
}

//Make a byte to give to a 7 segment display
byte makeSegment(int num, boolean dot, int dir, int type) {
  byte out = 0x00;
  for (int i=0; i<7; i++)
    out += (leds[num][i]*pins[type][remap[dir][i]]);
  if (dot)
    out += 0x08;
  if (num < 0)
    return 0xFF;
  return (0xFF - out);
}

//Write out to the shift registers
void writeLEDS(byte data[]) {
  digitalWrite(outputenable,HIGH);
  digitalWrite(latchPin, LOW);
  for (int i=0;i<segments; i++)
    shiftOut(dataPin, clockPin, MSBFIRST, data[i]);
  digitalWrite(latchPin, HIGH);
  digitalWrite(outputenable,LOW);
}




/*

void periodicUpdate( struct timeval tv, char buttonPressed[] ){

	buttonUpdate();
	
	short clockI;

	if( boardState == NORMAL_MODE ){
		//Normal State Code
		
		elapsedTime = tv.tv_sec - initialTime;
		
		if( buttons[1].pressed ){ 
			clocks[0].running = 0;
			boardState = PAUSED_MODE;
		}
		else if( buttons[0].pressed ) clocks[0].running = 1;
		
		if( buttons[4].pressed && homeScore <= 99) homeScore++;
		else if( buttons[5].pressed && homeScore > 0) homeScore--;
		if( buttons[8].pressed && awayScore <= 99) awayScore++;
		else if( buttons[9].pressed && awayScore > 0) awayScore--;
		
		if( buttons[6].pressed && buttons[6].pressed >= 119){
			clocks[2].running = 1;
			clocks[2].maxTime = 120;
			clocks[2].curTime = 120;
		} else if( buttons[6].pressed){
			clocks[2].running = 1;
			clocks[2].maxTime = 300;
			clocks[2].curTime = 300;
		}
		
		if( buttons[6].held ){
			clocks[2].running = 0;
			clocks[2].curTime = 0;
		}
		
		if( buttons[7].pressed && buttons[7].pressed >= 119){
			clocks[3].running = 1;
			clocks[3].maxTime = 120;
			clocks[3].curTime = 120;
		} else if( buttons[6].pressed){
			clocks[3].running = 1;
			clocks[3].maxTime = 300;
			clocks[3].curTime = 300;
		}
		
		if( buttons[7].held ){
			clocks[3].running = 0;
			clocks[3].curTime = 0;
		}
		
		if( buttons[10].pressed && buttons[10].pressed >= 119){
			clocks[4].running = 1;
			clocks[4].maxTime = 120;
			clocks[4].curTime = 120;
		} else if( buttons[6].pressed){
			clocks[4].running = 1;
			clocks[4].maxTime = 300;
			clocks[4].curTime = 300;
		}

		if( buttons[10].held ){
			clocks[4].running = 0;
			clocks[4].curTime = 0;
		}
		
		if( buttons[11].pressed && buttons[11].pressed >= 119){
			clocks[5].running = 1;
			clocks[5].maxTime = 120;
			clocks[5].curTime = 120;
		} else if( buttons[6].pressed){
			clocks[5].running = 1;
			clocks[5].maxTime = 300;
			clocks[5].curTime = 300;
		}
		
		if( buttons[11].held ){
			clocks[5].running = 0;
			clocks[5].curTime = 0;
		}		
		
		if( boardState != PAUSED_MODE )
			for( clockI = 0; clockI < 6; clockI++ )
				if( clocks[clockI].running )
					 clocks[clockI].curTime -= elapsedTime; 
	} else if (boardState == PAUSED_MODE) {
		//Paused State Code
		
		if( timeOut ){
			curTimeOutTime += (initialTime - tv.tv_sec);
			if( curTimeOutTime == 0 ){ timeOut = 0; } 
		}
		
		if( buttons[6].held && buttons[10].held ) clocks[0].curTime = 900;
		if( buttons[7].held && buttons[11].held ) boardState = SPECIAL_MODE;
		else if( buttons[0].pressed ) {
			boardState = NORMAL_MODE;
			timeOut = 0;
			initialTime = tv.tv_sec;
		}
		
		if( buttons[2].pressed && period < 2){ period++; }
		else if( buttons[3].pressed && period > 0){ period--; }

		if( buttons[4].pressed || buttons[5].pressed || buttons[8].pressed || buttons[9].pressed ){
			//start timeout
			timeOut = 1;
			curTimeOutTime = 120;
			initialTime = tv.tv_sec;
		}

	} else if (boardState == SPECIAL_MODE) {
		//Special State Code
		if( buttons[4].pressed  ) clocks[0].curTime += 60;
		else if( buttons[5].pressed && clocks[0].curTime/60 > 0) clocks[0].curTime -= 60;
		else if( buttons[8].pressed ) clocks[0].curTime++;
		else if( buttons[9].pressed && clocks[0].curTime > 0 ) clocks[0].curTime--;
		
		if( buttons[7].held && buttons[11].held ) boardState = PAUSED_MODE;
		else if( buttons[6].pressed && buttons[10].pressed ){
			//specialized settings menu
		}
	}
}

void buttonUpdate(){
	
	bool last;
	short butIndex;
	//set up the raw states of all the buttons currently
	for( butIndex = 0; butIndex < NUM_BUTTONS; butIndex++ ){
		last = buttons[butIndex].raw_state;
		if( last && buttons[butIndex].raw_state ){
			buttons[butIndex].holdCount++;
			if( buttons[butIndex].holdCount >= MIN_HOLD_COUNT ) buttons[butIndex].held = 1;
		}
		else if( !buttons[butIndex].raw_state ){
			buttons[butIndex].holdCount = 0;
			buttons[butIndex].held = 0;

		}

		//this allows for auto button pressed and release after one time unit
		if( buttons[butIndex].holdCount == 1 ){ buttons[butIndex].pressed = 1; }
		else{ buttons[butIndex].pressed = 0; }

	}
}

void getScore( short scoreNum, char scoreData[] ){

	if( scoreNum ){
		//away
		scoreData[0] = homeScore / 10;
		scoreData[1] = awayScore % 10;
	} else {
		//home
		scoreData[0] = homeScore / 10;
		scoreData[1] = homeScore % 10;
	}
}

void getClock( short ClockNum, char clockData[] ){

	short sec, min;

	//special case of during a timeout
	if( ClockNum == 0 && timeOut ) {
		sec = curTimeOutTime % 60;
		min = curTimeOutTime / 60;
	}
	//any other time
	else {	
		sec = clocks[ClockNum].curTime % 60;
		min = clocks[ClockNum].curTime / 60;
	}
	

	clockData[0] = min / 10;
	clockData[1] = min % 10;

	clockData[2] = sec / 10;
	clockData[3] = sec % 10;

}

short getPeriod(){ return period; }

*/


byte datas[10]={0,0,0,0,0,0,0,0,0,0};
void loop() {
        datas[0] = makeSegment(-1, false,dir[0],1);
        datas[1] = makeSegment(-1,false,dir[1],0);
        datas[2] = makeSegment(5,false,dir[2],0);
        datas[3] = makeSegment(3,false,dir[3],0);
        datas[4] = makeSegment(1,false,dir[4],0);
        datas[5] = makeSegment(8,false,dir[5],0);
        datas[6] = makeSegment(0,false,dir[6],0);
        datas[7] = makeSegment(0,false,dir[7],0);
        datas[8] = makeSegment(8,false,dir[8],0);
  /*
  
  //arguments: Number (0-9), Dot point (0,1), Direction (0,1), Segment type (0,1)=(Large,Small)
  byte tmp = makeSegment(0, false,dir[0],1);
  datas[0] = tmp;
  for (int i=1;i<9;i++){
    byte tmp = makeSegment(i, false,dir[i],0);
    datas[i] = tmp;
  }
  */
  writeLEDS(datas);
  delay(500);
}

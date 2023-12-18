//pins defined
int output_latchPin = 5;
int output_clockPin = 6;

int output_dataPin_anod = 4;
int output_dataPin_catod = 10;

byte datanod;
byte datacatod;
int dataArrayAnod[9];
byte dataArrayCatod[9];


void setup() {
  pinMode(output_latchPin, OUTPUT);
  Serial.begin(115200);



  dataArrayAnod[0] = 0;
  dataArrayAnod[1] = 1;
  dataArrayAnod[2] = 2;
  dataArrayAnod[3] = 4;
  dataArrayAnod[4] = 8;
  dataArrayAnod[5] = 16;
  dataArrayAnod[6] = 32;
  dataArrayAnod[7] = 64;
  dataArrayAnod[8] = 128;




  dataArrayCatod[0] = 0xFF;  //1111 1111
  dataArrayCatod[1] = 0xFE;  //1111 1110
  dataArrayCatod[3] = 0xFD;  //1111 1101
  dataArrayCatod[3] = 0xFB;  //1111 1011
  dataArrayCatod[4] = 0xF7;  //1111 0111
  dataArrayCatod[5] = 0xEF;  //1110 1111
  dataArrayCatod[6] = 0xDF;  //1101 1111
  dataArrayCatod[7] = 0xBF;  //1011 1111
  dataArrayCatod[8] = 0x7F;  //0111 1111
}

void loop() {
  /*
   * first of all we will set them to off, in case of noice on cable or from upload 
   * then it will take each one of them and light it up
   * until all leds were on. when it will get to the nineth led will upload to the second shift register in series
   */
  for (int shiftCount = 0; shiftCount < 256; shiftCount++) {


    digitalWrite(output_latchPin, LOW);

    //  shiftOut(output_dataPin_catod, output_clockPin, datacatod);
    shiftOut(output_dataPin_anod, output_clockPin, MSBFIRST, shiftCount);

    digitalWrite(output_latchPin, HIGH);

    delay(100);
  }
}

/*

void shiftOut(int mydataPin, int myClockPin, byte myDataOut) {

  int i = 0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(mydataPin, OUTPUT);

 //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(mydataPin, 0);
  digitalWrite(myClockPin, 0);



  for (i = 7; i >= 0; i--)  {
    digitalWrite(myClockPin, 0);


//if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    //if we are at i=5 and our value is
    // %11010100 it would the code compares it to %00100000 
    // and proceeds to set pinState to 0.
    // and so on until all 8 bit data is transmited
    if ( myDataOut & (1 << i) ) {
      pinState = 1;
    }
    else {
      pinState = 0;
    }
//send information bit by bit, until the array is finished
    digitalWrite(mydataPin, pinState);
 //use the LOW-HIGH state to register the change
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(mydataPin, 0);
  }

  digitalWrite(myClockPin, 0);
}

*/
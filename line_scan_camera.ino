
  // THE PINS OF THE LINE SCAN CAMERA TSL-1401DB.
 
 #define CLK   2   //camera clock input is connected to pin 2 of arduino. 
 #define SI    3   //camera serial input is connected to pin 3 of arduino.
 #define Aout  A0  // the analog output of the camera is connected to the A0 pin of the arduino, and also connected to oscilloscope.
 
unsigned int captpix[128];             //FOR STORE THE DIFFENTS VALUES OF EACH PIXEL.
    
void setup() 
{
  pinMode(CLK,OUTPUT);
  pinMode(SI,OUTPUT);
  pinMode(Aout,INPUT);        //THE ANALOG OUTPUT OF THE CAMERA is connected to the arduino board.
  Serial.begin(9600);         // IF YOU WANT TO SEE THE ANALOG OPPUTS VALUES OF THE CAMERA OF EACH PIXEL

}
/************************************************************************/

// WITH THIS FUNCTION YOU CAN SEE THE CAMERA'S ANALOG OUTPUT IN THE OSCILLOSCOPE. YOU CAN WATCH MY VIDEO IN MY YOUTUBE CHANNEL. see page 5 of the datasheet, figure 1 and 2.
void timming(void)
{
  
  int time=170;
  digitalWrite(SI, HIGH);
  delayMicroseconds(time/2);
  digitalWrite(CLK, HIGH);
  delayMicroseconds(time/2);
  digitalWrite(SI, LOW);
  delayMicroseconds(time/2);
  digitalWrite(CLK, LOW);
  delayMicroseconds(time);

  for(int contpixel=0;contpixel<128;contpixel++)
  {

    digitalWrite(CLK, HIGH);
    delayMicroseconds(time);
    digitalWrite(CLK, LOW);
    delayMicroseconds(time);

  }

  digitalWrite(CLK, HIGH);
  delayMicroseconds(time);
  digitalWrite(CLK, LOW);
  delayMicroseconds(time);
}
/************************************************************************/


//WITH THIS FUNCTION THE CAMERA PROCESS THE ANALOG OUTPUT FOR MOVE THE SERVO.
// IS VERY IMPORTAND THAT YOU LOOK THAT I AM NOT USING TIMER INTERRUPTS IN THIS CODE, THIS CODE IS JUST FOR DEMOSTRATION.
// PREVIOUSLY I WILL FIX THIS CODE. AND I AM SORRY, BEACUSE EXPLAIN MY CODE FOR THIS MEDIUM IS VERY DIFFICULT.
void ADC_READ_CAMERA(void)  
{
  
  int time=170;
  digitalWrite(SI, HIGH);
  delayMicroseconds(time/2);
  digitalWrite(CLK, HIGH);
  delayMicroseconds(time/2);
  digitalWrite(SI, LOW);
  delayMicroseconds(time/2);
  digitalWrite(CLK, LOW);
  delayMicroseconds(time);

  for(int contpixel=0;contpixel<128;contpixel++)
  { 
    digitalWrite(CLK, HIGH);
    captpix[contpixel]=analogRead(Aout);
    delayMicroseconds(time);
    digitalWrite(CLK, LOW);
    delayMicroseconds(time);
  }
  //impre();                                                  //IF YOU WANT TO SEE THE 128 VALUES READ FOR THE ADC, YOU ENABLE THIS FUNCTION.
                                                             // IF YOU ENABLE THE IMPRE() FUNCTION, ALSO YOU NEED ENABLE THIS SERIAL PRINT.
  delay(20);
}

 /************************************************************************/
 void impre()
{
  for( int j=0; j<128;j++)
  {
    Serial.print(j);
    Serial.print("=");
    Serial.print(captpix[j]);
    Serial.println();
    delay(75);
  }
}
 /************************************************************************/
 void loop() 
{      
  timming();              // if this function is activated, dont active the ADC_READ_CAMERA() and impre() functions. use this function when the
                          // A0 pin of the camera is connected to the oscilloscope.
  //ADC_READ_CAMERA();
  // impre();             // enable this function if you want the 128 output analog values in the serial monitor of arduino, but
                          // if you use this function you can not see the analog output signal in the osiclloscope.
}


// Libraries needed
  #include <Servo.h>
  #include <EasyButton.h>
  #include "avdweb_VirtualDelay.h" //virtual delay library 1.0.5 (at least this version/ the owner didn't edit his version sheet when he realeased the 1.0.5 so it will indicate 1.0.3)
  #include <EasyButton.h>
  #include <Adafruit_NeoPixel.h>
  #ifdef __AVR__
  #include <avr/power.h>
  #endif

  #define PIN            2      // neopixel details
  #define NUMPIXELS      5

  #define BROCHE_POTENTIOMETRE1  A0     // joysticks
  #define BROCHE_POTENTIOMETRE2  A1



  VirtualDelay delay_kick1(millis);     //define 2 virtual delays in millis
  VirtualDelay delay_kick2(millis);

  EasyButton btnhit1(7);      //define buttons (microswitch) for robots chests (to detect impact)
  EasyButton btnhit2(11);
  int x=0 ;                   //variables used for led indications in neopixel (score)
  int y=4;

  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//robot 1

      //robot 1 Servos
        Servo servo_rb1_l;  //legs
        Servo servo_rb1_a;  //arm
      // robot 1 joystick
        int s_potard1;
     //robot 1 punch button
      EasyButton btn1(12);



//robot 2
      //robot 2 Servos
        Servo servo_rb2_l;    //legs
        Servo servo_rb2_a;    //arm
      // robot 2 joystick
        int s_potard2;
     //robot 2 punch button
      EasyButton btn2(4);

void setup() {
    Serial.begin(9600);
    pinMode(BROCHE_POTENTIOMETRE1, INPUT) ;//  joysticks initialization
    pinMode(BROCHE_POTENTIOMETRE2, INPUT) ;
    btn1.begin();                          //  buttons initialization
    btn2.begin();
    btnhit1.begin();
    btnhit2.begin();
    btnhit1.onPressed(boutonPresshit1);   //  When microswiths on robot chest is pressed calls (boutonPresshitROBOTNUMBER)
    btnhit2.onPressed(boutonPresshit2);
    btn1.onPressed(kick1);                //  When button on handle is pressed calls (kickROBOTNUMBER)
    btn2.onPressed(kick2);
    servo_rb1_l.attach(9);                //  Servos initialization
    servo_rb1_a.attach(10);
    servo_rb2_l.attach(5);
    servo_rb2_a.attach(6);
    servo_rb1_a.write(0);
    servo_rb2_a.write(0);

    // Virtual Delay : This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    // End of trinket special code

    pixels.begin(); // This initializes the NeoPixel library.

    pixels.setPixelColor(0, pixels.Color(150,0,0)); // This initializes score-counter
    pixels.setPixelColor(4, pixels.Color(0,0,150));
    pixels.show();


}


void loop() {
  btn1.read();                                  //read buttons state constantly
  btn2.read();
  btnhit1.read();
  btnhit2.read();
  s_potard1 = analogRead(BROCHE_POTENTIOMETRE1);
  s_potard1 = map(s_potard1,0,1023,0,180);      //mapping values from joystick (0-180 degrees : Servos extreme angles)
  s_potard2 = analogRead(BROCHE_POTENTIOMETRE2);
  s_potard2 = map(s_potard2,0,1023,0,180);
  servo_rb1_l.write(s_potard1);
  servo_rb2_l.write(s_potard2);

    if(delay_kick1.elapsed()){    //detects if virtual delays launched in function (kick1) is over and set arm's servos to initial position (0)
     servo_rb1_a.write(0);
  }
    if(delay_kick2.elapsed()){    //detects if virtual delays launched in function (kick2) is over and set arm's servos to initial position (0)
     servo_rb2_a.write(0);
  }

  if(x==4){                       //red player wins : game over (x==4 : all LEDs are red)
   pixels.setPixelColor((x), pixels.Color(255,0,0));
   pixels.show();
   delay(50);
   pixels.setPixelColor((x), pixels.Color(0,0,0));
   pixels.show();
   delay(150);
   pixels.setPixelColor((x), pixels.Color(255,0,0));
   pixels.show();
   delay(50);
   pixels.setPixelColor((x), pixels.Color(0,0,0));
   pixels.show();
   delay(150);
   pixels.setPixelColor((x), pixels.Color(255,0,0));
   pixels.show();
   delay(8000);

  }
  if(y==0){                        //blue player wins : game over (y==0:all LEDs are blue)
   pixels.setPixelColor((y), pixels.Color(0,0,255));
   pixels.show();
   delay(50);
   pixels.setPixelColor((y), pixels.Color(0,0,0));
   pixels.show();
   delay(150);
   pixels.setPixelColor((y), pixels.Color(0,0,255));
   pixels.show();
   delay(50);
   pixels.setPixelColor((y), pixels.Color(0,0,0));
   pixels.show();
   delay(150);
   pixels.setPixelColor((y), pixels.Color(0,0,255));
   pixels.show();
   delay(8000);
  }

}

void kick1() {      //robot 1 kick: sets arm's servo on 90 degrees and launches a virtual delay
    servo_rb1_a.write(90);
delay_kick1.start(200);


}

void kick2() {    //robot 2 kick: sets arm's servo on 90 degrees and launches a virtual delay
    servo_rb2_a.write(90);
delay_kick2.start(200);
}


            //If impact detected on robots torsos, add 1 point to opponent and light one more LED of opposite player color
            //x= led position for blue robot  y=led position for red robot
            //example: if blue gets hit in the chest : (if x=y-1 :( x=x-1))  and  y=y-1  and LED N°y becomes red
            //example: if red gets hit in the chest : (if y=x+1 :( y=y+1))  and  x=x+1  and LED N°x becomes blue
            //in loop: if y=0: red wins
            //in loop: if x=4: blue wins
void boutonPresshit1(){

          if (y==(x+1))
      {
         y++;
      }
      x=x+1;
      pixels.setPixelColor((x), pixels.Color(150,0,0));
      pixels.show();
}

void boutonPresshit2(){

          if (x==(y-1))
      {
         x--;
      }
     y=y-1;
     pixels.setPixelColor((y), pixels.Color(0,0,150));
     pixels.show();


}

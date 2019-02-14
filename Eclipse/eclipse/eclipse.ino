/*
 *  Eclipse game :  An arduino based circular racing game.
 *  Created by : Simon Renault, Christophe Le Conte.
 *  Dates : January 2019.
 *
*/
// @todo : add a max score
// @todo : merge player logic
// @todo : optimize memory usage
// @todo : alow for easier understanding of tick and render cycles.

#include <FastLED.h>


// Led array definition
#define NUM_LEDS 74
CRGBArray<NUM_LEDS> leds;

int LED_OFFSET = 2;
int LED_LENGTH = NUM_LEDS - LED_OFFSET;

// Speed of the speed increment
float inc = 0;
int inc_speed = 50 ;

unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;

// Speed of the render clock
int tick = 30;

// Player base params
int PLAYER_OFFSET = NUM_LEDS/4;
int PLAYER_SIZE = 3;

// Player 1 variables
int PLAYER_1_PIN = 0;
int PLAYER_1_READING;
int PLAYER_1_POS = NUM_LEDS - PLAYER_OFFSET;
int PLAYER_1_DIR = 1;

// Player 2 variables
int PLAYER_2_PIN = 1;
int PLAYER_2_READING;
int PLAYER_2_POS = NUM_LEDS/2 - PLAYER_OFFSET;
int PLAYER_2_DIR = 1;


// Global app variables
int APP_STATE = 2;
int APP_SLEEP_DELAY = 200;
int APP_SLEEP_COUNTER = 0;

// Direction and speed params
int dir = 1;


void setup() {
  //Serial.begin(9600); // Envoi de message de déboggage sur connexion série
  FastLED.addLeds<NEOPIXEL, 9>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {

  // initalize the loops
  unsigned long currentMillis = millis();
  unsigned long currentMillis1 = millis();

  // update the values of the sensors
  PLAYER_1_READING = analogRead(PLAYER_1_PIN);
  PLAYER_2_READING = analogRead(PLAYER_2_PIN);

  Serial.println(PLAYER_1_READING);
  //Serial.println(PLAYER_2_READING);



  // speed inc loop
  if (currentMillis1 - previousMillis1 >= inc_speed) {
    previousMillis1 = currentMillis1;

    tick < 20 ? tick = tick :tick = tick -1 ;
  }


  // slow render loop, update every render tick
  // not suitable for any reaing from the board
  if (currentMillis - previousMillis >= tick) {
    previousMillis = currentMillis;

    //controle the different states of the app
    gameController();

  }

  // render everything on the led strip
  FastLED.show();
}


void gameController(){

  /*
   *  The game controller handle the main logic of the app.
   *
  */

  if(APP_STATE == 1){
    restart();
    for( int i = LED_OFFSET; i < NUM_LEDS  - 1; i++){
        leds[i] = CRGB(200,1,1);
    }
    APP_SLEEP_COUNTER ++;
    if( APP_SLEEP_COUNTER > APP_SLEEP_DELAY){
      APP_STATE = 2;
      APP_SLEEP_COUNTER = 0;
    }
  }else if(APP_STATE == 2){
    restart();
    for( int i = LED_OFFSET; i < NUM_LEDS  - 1; i++){
        i <= NUM_LEDS/2 ? leds[i] = CRGB(22, 60, 200) :  leds[i] = CRGB(255, 60, 0);
    }

  }else{
    // playing state handled here
    reset();
    PLAYER_1();
    PLAYER_2();
    checkwin();
  }
}


void PLAYER_1(){

  /*
   *  The player 1 hadle the logic and display of the player 1
   *
  */


  // update the direction according to the sensor value
  PLAYER_1_READING > 400 ? PLAYER_1_DIR = 1 : PLAYER_1_DIR = -1;

  //render the player
  for(int i = 0; i < PLAYER_SIZE ; i++){
    int player_pos = get_led(PLAYER_1_POS + i);
    leds[player_pos] = CRGB(22, 60, 200);
  }

  //update the player pos
  PLAYER_1_POS = get_led(PLAYER_1_POS + PLAYER_1_DIR);
}


void PLAYER_2(){

  /*
   *  The player 1 hadle the logic and display of the player 1
   *
  */

  // update the direction according to the sensor value
  PLAYER_2_READING > 400 ? PLAYER_2_DIR = 1 : PLAYER_2_DIR = -1;

  //render the player
  for(int i = 0; i < PLAYER_SIZE ; i++){
    int player_pos = get_led(PLAYER_2_POS + i);
    leds[player_pos] = CRGB(255, 60, 0);
  }

  //update the player pos
  PLAYER_2_POS = get_led(PLAYER_2_POS + PLAYER_2_DIR);
}


void restart(){

  /*
   *  The only goal of this function is to reset the app to it's initial state if both pads are pressed
   *  Should be called after each death
   *
  */

  if(PLAYER_1_READING < 500 && PLAYER_2_READING < 500 ){

    // reset all params of the game
    PLAYER_1_POS = NUM_LEDS - PLAYER_OFFSET;
    PLAYER_2_POS = NUM_LEDS/2 - PLAYER_OFFSET;
    APP_STATE = 0;

    tick = 500;
  }
}


void checkwin(){

  /*
   *  This function handle all the logic of colision between the player
   *
  */

  // check for colision between the players
  for(int i = 0; i < PLAYER_SIZE ; i++){
    for(int j = 0; j < PLAYER_SIZE ; j++){
      int a = i + PLAYER_1_POS;
      int b = j + PLAYER_2_POS;
      if(a == b){
         // if there is a collision game state jump to one
         APP_STATE = 1;
      }
    }
  }
}


int get_led(int led){

  /*
   *  Helper function to help to query leds only inside of the giver range.
   *
  */

  if(led >= NUM_LEDS){
    return LED_OFFSET;
  }else if(led < LED_OFFSET){
    return NUM_LEDS -1 ; // start at led 0
  }else{
    return led;
  }
}


void reset(){

  /*
   *  Helper function erasing all the leds of the stip.
   *
  */

  for(int i = 0; i < NUM_LEDS; i++){
      leds[i] = CRGB(0, 0, 0);
  }
}

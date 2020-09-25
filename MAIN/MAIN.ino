//Created: 04.09.2017

//snake game for 5x8 LED matrix - the pins' high output turns on the transistor connecting the proper row and column to ground (or Ucc)
//the snake can be controlled by two push buttons - A0 to high for left; A1 high for right turn.
//these buttons need to have a pulldown resistor each
//by powering the arduino and the LED-matrix, the game immediately starts
//when the snake hits the wall or itself, the game restarts
//starting length and position is in snake::SETUP()

//only one LED is turned on at a time, so when the snake's
//body starts to fill in the matrix, there is a slight
//stroboscopic affect. After testing on friends, this
//"problem" became a feature, because it turned out
//that it makes the game more enjoyable.


#include "Arduino.h"
#include "snake.h"

snake player1;                  //object containing all the functions for game is created
unsigned long prevmiles = 0;    //prevmiles will contail previous time for button state watching
bool toleft = 0;                //these boolians are needed to structure the loop efficiently.
bool toright = 0;               //the button is watched and the screen is refreshed continuously until it is time to update the snake
bool roller = 0;                //between two updates of the snake the button can be pressed only once and in one direction
bool watcher = 0;               //then it is registered and locked until next cycle

void setup() {                  //SETUP---------SETUP--------SEUP-------SETUP-------SETUP-------SETUP---------SETUP--------SETUP----------SETUP-------SETUP----------SETUP
  for (int i=0; i<14; i++){
    pinMode(i, OUTPUT);         //pins are set as output
  }      
  digitalWrite(0, HIGH);        //pin0 is used as pullup for button
  player1.SETUP();              //setting snake object to initial values
}

void loop() {                   //LOOP-------------------LOOP-------------------LOOP-------------------LOOP-------------------LOOP-------------------LOOP-------------------LOOP
  
  unsigned long currentmiles=millis();    //currentmiles will store time

  if (roller ==0 && digitalRead(A0) == HIGH){     //watching button #1. if high value is read, turning right in next move is locked
    toright =1;
    roller=1;
    watcher =1;
  }

  if (roller ==0 && digitalRead(A1) == HIGH){     //watching button #1. if high value is read, turning left in next move is locked
    toleft =1;
    roller=1;
    watcher =1;
  }
    

  
//AFTER ENOUGH TIME HAS PASSED:
  //--------------------------------------------------------------------------------------------------------------------------------------
  if ( currentmiles-prevmiles>500){         //here the "speed of game" can be set. once this time has passed, the contained command will be executed
    if(toright==1){               
      player1.right();
    }                               //here checking if there is information on turning

    if(toleft==1){
      player1.left();
    }
    player1.snakedate();            //updating snake
    prevmiles=millis();             //resetting timer
   watcher = 0;                     //resetting watcher - new value for turning can be locked in
   toright=0;                       
   toleft=0;
  }                             //-----------------------------------------------------------------------------------------------------------------------------------------------------
  
  player1.draw();                     //draw boolian matrix(matr[5][8])
  if (watcher == 0 && digitalRead(A0) == LOW && digitalRead(A1) == LOW){      //sets back roller to 0 after every update only - when watcher is 0 again.
   roller = 0;
   watcher = 1;
  }

  

}

#include "Arduino.h"
#include "snake.h"


void snake::SETUP(){                                      //-------------------------------SETUP------SETUP-------SETUP----------------------------------------------
  snaketrix_clean();             //set bool matrix to 0
  for (int i =0; i<40; i++){      //SET PLAYER ARRAY TO 0,0
    player[i].x= 0;
    player[i].y =0;  
  }
  len = 4;                        //INITIAL LENGTH
  player[0].x = 5;                //INITIAL POSITION FOR FIRST PART
  player[0].y = 1;
  movex=0;                        //INITIAL MOVEMENT
  movey=1;
  newapple();                     //CREATE APPLE RANDOM
}


void snake::snakedate(){                                        //--------------UPDATE--SNAKE------------------UPDATE--SNAKE-----------------------UPDATE--SNAKE------------------
  bool ded = 0;                   //BOOL TO CHECK IF SNEAK BIT ITSELF
  
  for (int i =0; i<len-1; i++){
    if (player[0].x+movex == player[i].x && player[0].y+movey == player[i].y)   //CHECK IF SNEAK IS GOING TO BITE ITSELF
      ded=1; 
    }
                                                                            //IF NOT, THEN:
  
  if (ded == 0 && player[0].x+movex>=1 && player[0].x+movex<=5 && player[0].y+movey>=1 && player[0].y+movey<=8 ){   //CHECK IF SNEAK IS HITTING WALL 
                                                                                                  //IF NOT, THEN::
    
  for (int i = len; i > 0; i--) {           //copy player vector elements one back
      player[i].x = player[i-1].x;
      player[i].y = player[i-1].y;
    }

  if (player[0].x-1 == apple.x && player[0].y-1 == apple.y){          //CHECKING IF SNEAK HAS EATEN
    len++;                                                            //IF YES, LEN++ AND CREATE NEW RANDOM APPLE
    newapple();
  }
    
  player[0].x+=movex;
  player[0].y+=movey;               //set new coordinates for head of snake
    snaketrix_clean();                           //clean snaketrix
  for (int i = 0; i<len; i++){                 //set snaketrix with new coordinates
    matr[player[i].x-1][player[i].y-1]=1;
  }
  matr[apple.x][apple.y] = 1;
  
  
 }
 else                                                         //IF SNEAK IS DEAD FOR SOME REASONE ABOVE, RESET GAME
 SETUP();

}

void snake::snaketrix_clean(){          //CLEAN BOOL MATRIX FUNCTION
  for (int i =0; i<5; i++)
    for (int j =0; j<8; j++)
      matr[i][j] = 0;
}

void snake::right(){                    //TURN RIGHT - SWITCH STATEMENTS
  switch(movex){
    case 0:
      switch(movey){
        case 1:
          movex=-1;
          movey=0;
          break;
        case -1:
          movex=1;
          movey=0;
          break;
      }
      break;
    case 1:
      movex=0;
      movey=1;
      break;
    case -1:
      movex=0;
      movey=-1;
  }
  
}

void snake::left(){                 //TURN LEFT - SWITCH STATEMENTS

switch(movex){
    case 0:
      switch(movey){
        case 1:
          movex=1;
          movey=0;
          break;
        case -1:
          movex=-1;
          movey=0;
          break;
      }
      break;
    case 1:
      movex=0;
      movey=-1;
      break;
    case -1:
      movex=0;
      movey=1;
  }
  
   
}


  void snake::draw() {            //DRAW BOOL MATRIX TO LED MATRIX
    fresh();
    for (int i =0; i<5; i++)
      for (int j =0; j<8; j++){
        if (matr[i][j] == 1){
          digitalWrite(i+1, HIGH);
          digitalWrite(j+6, HIGH);
          delay(1);
          fresh();
        }
      }
  }


  void snake::fresh(){                //sets every output to low
  for (int i =1; i<14; i++){
    digitalWrite(i, LOW);
    }
}


void snake::LED(int x, int y){      //lights up led called by coordiantes
   digitalWrite(x+1, HIGH);         //is not used, but left it here for help
   digitalWrite(y+6, HIGH);         //to understand printing later
}


void snake::newapple(){
bool vectorcomp;

  do{
    vectorcomp = 0;
    apple.x=random(0,5);
    apple.y=random(0,8);

    for (int i =0; i<=len; i++){
       if (player[i].x-1==apple.x && player[i].y-1==apple.y)
         vectorcomp=1;
   }
    
  }while(vectorcomp);
}

  //-----------------------------------------------------------VECTOR FUNCTIONS-------------------------------VECTOR FUNCTIONS-------------------------------------------------------




  void vector::setx(int a){
  x=a;
}

void vector::sety(int a){
  y=a;
}



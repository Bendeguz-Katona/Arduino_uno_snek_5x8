#ifndef snake_h
#define snake_h

class vector{     //vector is used as an array to contain positions of snake body
  public:
  unsigned int x;   
  unsigned int y;
  public:
  void setx(int a);
  void sety(int a);
  uint8_t takex();        
  uint8_t takey();
};

class snake{
  private:
  bool matr[5][8];        //boolian matrix - this is being drawn to LED matrix directly
  vector player[40];      //vector array containing positions of snake body
  uint8_t len;            //len contains instantaneous value for length of snake
  signed int movex;       //contains movement in dir.x
  signed movey;           //contains movement in dir.y
  vector apple;           //contains coordinates of apple
  

  public:
  void SETUP();          //self explaining
  void snakedate();      //update function - see snake.cpp
  void snaketrix_clean();//sets boolian matrix to default (0) values (no LED is on when drawn)
  void right();          //turn right
  void left();           //turn left
  void draw();           //draw boolian matrix to LED matrix
  void fresh();          //turns every LED off
  void LED(int x, int y);//turns on LED named by coordinates
  void newapple();       //creates new apple that does not coincide with body of snake ----- NOT EFFICIENT AT THE TIME!!
  
};





#endif

//the app changes charachter of wheels' spin depending on Serial Monitor input

// '!' means important
// '?' means got to solve

#define DIR1 2          // number of pin which defines direction of engine 1 spin
#define SPD1 3          // number pin which defines speed of engine 1 spin
#define DIR2 4          // number of pin which defines direction of engine 2 spin
#define SPD2 5          // number of pin which defines speed of engine 2 spin

//1 - right engine, 2 - left engine

//spin directions
bool forward = false;
bool backward = true;

//speeds
int move = 100;            
int stop = 0;
 
void setup() 
{ 
    Serial.begin(9600);
    pinMode(DIR1, OUTPUT);
    pinMode(DIR2, OUTPUT);  
} 
 
void loop() 
{
  if(Serial.readString() == "start\n") 
  {
    while(true)
    {
      Wheels_spin(forward, backward, move); //move forward
      char action = Serial.read();
      switch(action)
      {
        case 'l': 
          Wheels_spin(forward, forward, move); //turn left
          delay(2000); //? calculate angle of turn
          break;
        case 'r':
          Wheels_spin(backward, backward, move); //turn right
          delay(2000);
          break;
        case 's':
          while (Serial.readString() != "start\n") 
          {
            Wheels_spin(forward, forward, stop); //stop 
          }
      }
    }
  }  
}

void Wheels_spin(bool dir1, bool dir2, int speed)
{
  digitalWrite(DIR1, dir1); 
  digitalWrite(DIR2, dir2); //! left wheel is installed in inverse position
  analogWrite(SPD1, speed);      
  analogWrite(SPD2, speed);  
}

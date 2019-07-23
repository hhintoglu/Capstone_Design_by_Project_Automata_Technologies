#define sag_direction_1 4
#define sag_direction_2 9
#define sol_direction_1 8
#define sol_direction_2 7
#define sag_motor 6
#define sol_motor 3
#define shooting 10
#define servo_max_deg 180
#define servo_min_deg 0
#define max_forward_speed 150
#define min_forward_speed -150
#define max_right_speed 100
#define min_right_speed -100

#include <Servo.h>

Servo sg90;

unsigned long int ft, lt, x, tfail;
int ch, chx[9][13];
int angle;
int pwm;

volatile long channel_length[] = {0, 0, 0, 0, 0, 0};
const int idx   = 10;
const int total = 11;
const int val   = 12;

int sag_motorc = 0;
int sol_motorc = 0;
int speedy = 0;
int right = 0; 

void setup() {
  sg90.attach(11);
  Serial.begin(9600);
  
  ft=0; lt=0; x=0; tfail=0; ch=0;
  for (int i=0; i<9; i++) {
    for (int j=0; j<13; j++) {
      chx[i][j]=0;
    }
  }
  pinMode(7,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), decodePPM, FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:
  channel_length[0] = chx[1][val];
  channel_length[1] = chx[2][val];
  channel_length[5] = chx[6][val]; 
  channel_length[2] = chx[3][val];

  speedy = map(channel_length[1],1000,2000,min_forward_speed,max_forward_speed);
  right = map(channel_length[0],1000,2000,min_right_speed,max_right_speed);
  sag_motorc = speedy-right;
  sol_motorc = speedy+right;
  
//  Serial.print(sag_motorc);
//  Serial.print("  ");
//  Serial.println(sol_motorc);

  if (sag_motorc>=0)
  {
    sag_motorc = sag_motorc;
    digitalWrite(sag_direction_1,HIGH);
    digitalWrite(sag_direction_2,LOW);
  }
  else{
    sag_motorc = -sag_motorc;
    digitalWrite(sag_direction_1,LOW);
    digitalWrite(sag_direction_2,HIGH);
  }

  if (sol_motorc>=0)
  {
    sol_motorc = sol_motorc;
    digitalWrite(sol_direction_1,HIGH);
    digitalWrite(sol_direction_2,LOW);
  }
  else{
    sol_motorc = -sol_motorc;
    digitalWrite(sol_direction_1,LOW);
    digitalWrite(sol_direction_2,HIGH);
  }
  
  analogWrite(sag_motor,sag_motorc);
  analogWrite(sol_motor,sol_motorc);
  
  angle = channel_length[2];
  angle = map(angle,1000,1900, servo_max_deg, servo_min_deg);
  sg90.write(angle);
  
 
  if(channel_length[5] >1900)
  {
    digitalWrite(shooting, HIGH);
  }
  else
  {
    digitalWrite(shooting, LOW);
  }
  
}

void decodePPM() {  
  lt    = micros();
  tfail = millis();
  x     = lt-ft;
  ft    = lt;
  
  if (x>3000) {
    ch          = 0;
    chx[0][val] = x;
  } 
  else {
    ch+=1;
    int indx       = chx[ch][idx];
    chx[ch][total] = chx[ch][total] - chx[ch][indx];
    chx[ch][indx]  = x;
    chx[ch][total] = chx[ch][total] + chx[ch][indx];
    chx[ch][idx]   = chx[ch][idx] + 1;

    if (chx[ch][idx]>9) {
      chx[ch][idx] = 0;
    }
    
    chx[ch][val] = chx[ch][total]/10;
  }
}

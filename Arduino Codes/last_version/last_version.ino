unsigned long int ft, lt, x, tfail;
int ch, chx[9][13];

#define sag_direction_1 4
#define sag_direction_2 3
#define sol_direction_1 8
#define sol_direction_2 7
#define sag_motor 6
#define sol_motor 9
#define shooting 10

volatile long channel_length[] = {0, 0, 0, 0, 0, 0};
const int idx   = 10;
const int total = 11;
const int val   = 12;

void DC_motor(boolean sag1, boolean sag2, boolean sol1, boolean sol2, byte solm, byte sagm){
    digitalWrite(sag_direction_1, sag1);
    digitalWrite(sag_direction_2, sag2);
    digitalWrite(sol_direction_1, sol1);
    digitalWrite(sol_direction_2, sol2);
    analogWrite(sol_motor, solm);
    analogWrite(sag_motor, sagm);
}

void setup() {

  Serial.begin(9600);
  ft=0; lt=0; x=0; tfail=0; ch=0;
  for (int i=0; i<9; i++) {
    for (int j=0; j<13; j++) {
      chx[i][j]=0;
    }
  }
  pinMode(2, INPUT_PULLUP);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), decodePPM, FALLING);
}



void loop() {

  channel_length[0] = chx[1][val];
  channel_length[1] = chx[2][val];
  channel_length[5] = chx[6][val]; 
  
  if((channel_length[0] > 900) && (channel_length[0] < 1200) && (channel_length[1] > 1800) && (channel_length[1] < 2000)) //1
  {
    DC_motor(HIGH,LOW,HIGH,LOW,0,255);
    Serial.println("Sol Motor:0 : Sag Motor:255");
  }
  
  else if((channel_length[0] > 1200) && (channel_length[0] < 1400) && (channel_length[1] > 1800) && (channel_length[1] < 2000))//2
  {
    DC_motor(HIGH,LOW,HIGH,LOW,128,255);
    Serial.println("Sol Motor:128 : Sag Motor:255");
  }

  else if((channel_length[0] > 1400) && (channel_length[0] < 1600) && (channel_length[1] > 1800) && (channel_length[1] < 2000)) //3
  {
    DC_motor(HIGH,LOW,HIGH,LOW,255,255);
    Serial.println("Sol Motor:255 : Sag Motor:255");
  }

  else if((channel_length[0] > 1600) && (channel_length[0] < 1800) && (channel_length[1] > 1800) && (channel_length[1] < 2000)) //4
  {
    DC_motor(HIGH,LOW,HIGH,LOW,255,128);
    Serial.println("Sol Motor:255 : Sag Motor:128");
  }
  
   else if((channel_length[0] > 1800) && (channel_length[0] < 2000) && (channel_length[1] > 1800) && (channel_length[1] < 2000)) //5
  {
    DC_motor(HIGH,LOW,HIGH,LOW,255,0);
    Serial.println("Sol Motor:255 : Sag Motor:0");
  }

  else if((channel_length[0] > 900) && (channel_length[0] < 1200) && (channel_length[1] > 1600) && (channel_length[1] < 1800)) //6 Sol Motor Ters
  {
    DC_motor(HIGH,LOW,LOW,HIGH,128,255);
    Serial.println("Sol Motor:128 : Sag Motor:255");
  }
  else if((channel_length[0] > 1200) && (channel_length[0] < 1400) && (channel_length[1] > 1600) && (channel_length[1] < 1800)) //7
  {
    DC_motor(HIGH,LOW,HIGH,LOW,0,128);
    Serial.println("Sol Motor:0 : Sag Motor:128");
  }
  else if((channel_length[0] > 1400) && (channel_length[0] < 1600) && (channel_length[1] > 1600) && (channel_length[1] < 1800)) //8
  {
    DC_motor(HIGH,LOW,HIGH,LOW,128,128);
    Serial.println("Sol Motor:128 : Sag Motor:128");
  }
  else if((channel_length[0] > 1600) && (channel_length[0] < 1800) && (channel_length[1] > 1600) && (channel_length[1] < 1800)) //9
  {
    DC_motor(HIGH,LOW,HIGH,LOW,128,0);
    Serial.println("Sol Motor:128 : Sag Motor:0");
  }
  else if((channel_length[0] > 1800) && (channel_length[0] < 2000) && (channel_length[1] > 1600) && (channel_length[1] < 1800)) //10 Sol ileri sag geri
  {
    DC_motor(LOW,HIGH,HIGH,LOW,255,128);
    Serial.println("Sol Motor:255 : Sag Motor:128");
  }

  else if((channel_length[0] > 900) && (channel_length[0] < 1200) && (channel_length[1] > 1400) && (channel_length[1] < 1600)) //11
  {
    DC_motor(HIGH,LOW,LOW,HIGH,255,255);
    Serial.println("Sol Motor:255 : Sag Motor:255");
  }

  else if((channel_length[0] > 1200) && (channel_length[0] < 1400) && (channel_length[1] > 1400) && (channel_length[1] < 1600)) //12
  {
    DC_motor(HIGH,LOW,LOW,HIGH,128,128);
    Serial.println("Sol Motor:128 : Sag Motor:128");
  }

  else if((channel_length[0] > 1400) && (channel_length[0] < 1600) && (channel_length[1] > 1400) && (channel_length[1] < 1600)) //13
  {
    DC_motor(HIGH,LOW,HIGH,LOW,0,0);
    Serial.println("Sol Motor:0 : Sag Motor:0");
  }

  else if((channel_length[0] > 1600) && (channel_length[0] < 1800) && (channel_length[1] > 1400) && (channel_length[1] < 1600)) //14
  {
    DC_motor(LOW,HIGH,HIGH,LOW,128,128);
    Serial.println("Sol Motor:128 : Sag Motor:128");
  }

  else if((channel_length[0] > 1800) && (channel_length[0] < 2000) && (channel_length[1] > 1400) && (channel_length[1] < 1600)) //15
  {
    DC_motor(LOW,HIGH,HIGH,LOW,255,255);
    Serial.println("Sol Motor:255 : Sag Motor:255");
  }

  else if((channel_length[0] > 900) && (channel_length[0] < 1200) && (channel_length[1] > 1200) && (channel_length[1] < 1400)) //16 Sag Motor İleri
  {
    DC_motor(HIGH,LOW,LOW,HIGH,128,255);
    Serial.println("Sol Motor:128 : Sag Motor:255");
  }

  else if((channel_length[0] > 1200) && (channel_length[0] < 1400) && (channel_length[1] > 1200) && (channel_length[1] < 1400)) //17
  {
    DC_motor(LOW,HIGH,LOW,HIGH,0,128);
    Serial.println("Sol Motor:0 : Sag Motor:128");
  }

  else if((channel_length[0] > 1400) && (channel_length[0] < 1600) && (channel_length[1] > 1200) && (channel_length[1] < 1400)) //18
  {
    DC_motor(LOW,HIGH,LOW,HIGH,128,128);
    Serial.println("Sol Motor:128 : Sag Motor:128");
  }

  else if((channel_length[0] > 1600) && (channel_length[0] < 1800) && (channel_length[1] > 1200) && (channel_length[1] < 1400)) //19
  {
    DC_motor(LOW,HIGH,LOW,HIGH,128,0);
    Serial.println("Sol Motor:128 : Sag Motor:0");
  }

  else if((channel_length[0] > 1800) && (channel_length[0] < 2000) && (channel_length[1] > 1200) && (channel_length[1] < 1400)) //20
  {
    DC_motor(LOW,HIGH,HIGH,LOW,255,128);
    Serial.println("Sol Motor:255 : Sag Motor:128");
  }

  else if((channel_length[0] > 900) && (channel_length[0] < 1200) && (channel_length[1] > 900) && (channel_length[1] < 1200)) //21
  {
    DC_motor(LOW,HIGH,LOW,HIGH,0,255);
    Serial.println("Sol Motor:0 : Sag Motor:255");
  }

  else if((channel_length[0] > 1200) && (channel_length[0] < 1400) && (channel_length[1] > 900) && (channel_length[1] < 1200)) //22
  {
    DC_motor(LOW,HIGH,LOW,HIGH,128,255);
    Serial.println("Sol Motor:128 : Sag Motor:255");
  }

  else if((channel_length[0] > 1400) && (channel_length[0] < 1600) && (channel_length[1] > 900) && (channel_length[1] < 1200)) //23
  {
    DC_motor(LOW,HIGH,LOW,HIGH,255,255);
    Serial.println("Sol Motor:255 : Sag Motor:255");
  }

  else if((channel_length[0] > 1600) && (channel_length[0] < 1800) && (channel_length[1] > 900) && (channel_length[1] < 1200)) //24
  {
    DC_motor(LOW,HIGH,LOW,HIGH,255,128);
    Serial.println("Sol Motor:255 : Sag Motor:128");
  }

  else if((channel_length[0] > 1800) && (channel_length[0] < 2000) && (channel_length[1] > 900) && (channel_length[1] < 1200)) //25
  {
    DC_motor(LOW,HIGH,LOW,HIGH,255,0);
    Serial.println("Sol Motor:255 : Sag Motor:0");
  }

  //if(channel_length[])

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






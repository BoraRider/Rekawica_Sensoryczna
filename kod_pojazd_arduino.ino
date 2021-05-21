#include <Arduino.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define in_1 3
#define in_2 4
#define in_3 5
#define in_4 6

#define enable_2 9
#define enable_1 10

int msg[1];
RF24 radio(7,8);

int odebrane=0;

// to jest ok
const uint64_t pipe = 0xE8E8F0F0E1LL;



void setup() {

  pinMode(in_1, OUTPUT);
  pinMode(in_2, OUTPUT);
  pinMode(in_3, OUTPUT);
  pinMode(in_4, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(enable_2, OUTPUT);
  pinMode(enable_1, OUTPUT);  


  digitalWrite(in_1, 1);
  digitalWrite(in_2, 0);
  analogWrite(enable_1, 0);

  digitalWrite(in_3, 0);
  digitalWrite(in_4, 1);
  analogWrite(enable_2, 0);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
 

}

void loop() {

  if (radio.available())
  {
    bool done = false;    
    while (!done)
    {
       radio.read(msg, 1);
       done= !done;
       Serial.println(msg[0]);
       odebrane = msg[0];
       //Serial.print(msg[1]);
       //Serial.println(msg[2]);
    if ((odebrane < 100) && (odebrane>80))
    {
      digitalWrite(in_3, 1);
      digitalWrite(in_4, 0);
      analogWrite(enable_2, 220);
      digitalWrite(in_1, 0);
      digitalWrite(in_2, 1);
      analogWrite(enable_1, 220);
      delay(10);
    }
    else
    {
      int tmp=(90-odebrane);
      if(tmp>255) tmp=255;
      analogWrite(enable_1, 165+tmp);
      analogWrite(enable_2, 165-tmp);
    }
    
    delay(10);}
  }
  else
  {
  //Serial.println("Radio nie dostępne");
      digitalWrite(in_3, 1);
      digitalWrite(in_4, 0);
      analogWrite(enable_2, 0);
      digitalWrite(in_1, 0);
      digitalWrite(in_2, 1);
      analogWrite(enable_1, 0);
  }
  delay(100);

}

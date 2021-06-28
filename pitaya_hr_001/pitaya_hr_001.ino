#define DEBUG 1
/* Include the HCMAX7219 and SPI library */
#include <HCMAX7219.h>
#include "SPI.h"
#include "Wire.h"

#define NUMBEROFDRIVERS 1
/* Set the LOAD (CS) digital pin number*/
#define LOAD 10
#define COMUT 5


/* Create an instance of the library */
HCMAX7219 HCMAX7219(LOAD);

/* Utilisation du capteur Ultrason HC-SR04 */

// définition des broches utilisées
int analogPin = A6;
int trig = 7;
int echo = 8;
long lecture_echo;
long cm;
int n = 0;
int val = 0;
int i = 0;

void setup() {
  Wire.begin();

  pinMode(COMUT, OUTPUT);
  pinMode(trig, OUTPUT);

  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  Serial.begin(9600);

  digitalWrite(COMUT, LOW);
  delay(100);
}

void loop() {

  val = analogRead(analogPin) / 2;
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo, HIGH);
  cm = lecture_echo / 58;

  sendi2c();

  if (cm == 0)
  {
    reset_hcsr04();
  }
  if (cm < val)
  {
    digitalWrite(COMUT, HIGH);
  }
  if (cm > val + 100)
  {
    i = i + 1;
  }
  if (i == 25)
  {
    i = 0;
    digitalWrite(COMUT, LOW);
  }
#ifdef DEBUG
  Serial.print("Distancem : ");
  Serial.println(cm);
#endif
  /* Clear the output buffer */
  HCMAX7219.Clear();
  /* Write some text to the output buffer */
  HCMAX7219.print7Seg(cm, 4);
  HCMAX7219.print7Seg(val, 8);
  /* Send the output buffer to the display */
  HCMAX7219.Refresh();
  delay(10);

}

void sendi2c()
{
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(cm);              // sends one byte
  Wire.endTransmission();    // stop transmitting
}

void reset_hcsr04()
{
  pinMode(echo, OUTPUT);
  digitalWrite(echo, LOW);
  delay(100);
  pinMode(echo, INPUT);
}

